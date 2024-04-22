#pragma once

#include <cstdint>
#include <llvm-14/llvm/ADT/APInt.h>
#include <llvm-14/llvm/IR/Constant.h>
#include <llvm-14/llvm/IR/DebugInfoMetadata.h>
#include <llvm-14/llvm/IR/InstrTypes.h>
#include <llvm-14/llvm/IR/Instruction.h>
#include <llvm-14/llvm/IR/Instructions.h>
#include <llvm-14/llvm/IR/Use.h>
#include <llvm-14/llvm/IR/Value.h>
#include <llvm-14/llvm/Support/Casting.h>
#include <llvm/ADT/APInt.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Operator.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <map>
#include <stdexcept>
#include <vector>

#include "AstVisitor.h"
#include "Common.h"
#include "frontend/Ast.h"
#include "frontend/Decl.h"
#include "frontend/Type.h"

namespace rvlang {
class CodeGen : public AstVisitor<CodeGen> {
private:
  std::unique_ptr<llvm::LLVMContext> m_context;
  std::unique_ptr<llvm::IRBuilder<>> m_irBuilder;
  std::unique_ptr<llvm::Module> m_theModule;
  std::map<std::string, llvm::Value *> NamedValues;

  std::map<std::uintptr_t, llvm::Value *> m_astIrMap;

  llvm::Value *getIr(void *p) {
    auto itor = m_astIrMap.find(reinterpret_cast<std::uintptr_t>(p));
    if (itor != m_astIrMap.end()) {
      return itor->second;
    }
    return nullptr;
  }

public:
  CodeGen()
      : m_context(std::make_unique<llvm::LLVMContext>()),
        m_irBuilder(std::make_unique<llvm::IRBuilder<>>(*m_context)),
        m_theModule(std::make_unique<llvm::Module>("my module", *m_context)) {
    m_traverseOrder = TraverseOrder::PostOrder;
  }
  ~CodeGen() {}

public:
  bool visitTranslationUnitDecl(TranslationUnitDecl *decl) { return true; }
  bool visitFunctionDecl(FunctionDecl *decl) {
    // create funtion prototype
    // for simplicity, param type only sypport 'int' and 'int*'
    std::vector<llvm::Type *> args;
    for (ParamDecl *param : decl->getParams()) {
      if (param->getType()->getKind() == Type::Kind::Integer) {
        args.push_back(llvm::Type::getInt32Ty(*m_context));
      } else if (param->getType()->getKind() == Type::Kind::Pointer) {
        if (llvm::dyn_cast<PointerType>(param->getType())
                ->getPointeeType()
                ->getKind() != Type::Kind::Integer) {
          ThrowRuntimeError("unsupported prarm type");
        }
        args.push_back(llvm::Type::getInt32PtrTy(*m_context));
      } else {
        ThrowRuntimeError("unsupported prarm type");
      }
    }
    // function return type only support 'int', 'int*' and 'void'
    llvm::FunctionType *ft = nullptr;
    switch (decl->getRetType()->getKind()) {
    case Type::Kind::Integer:
      ft = llvm::FunctionType::get(llvm::Type::getInt32Ty(*m_context), args,
                                   false);
      break;
    case Type::Kind::Void:
      ft = llvm::FunctionType::get(llvm::Type::getVoidTy(*m_context), args,
                                   false);
      break;
    case Type::Kind::Pointer:
      if (llvm::dyn_cast<PointerType>(decl->getRetType())
              ->getPointeeType()
              ->getKind() != Type::Kind::Integer) {
        ThrowRuntimeError("unsupported function result type");
      }
      ft = llvm::FunctionType::get(llvm::Type::getInt32PtrTy(*m_context), args,
                                   false);
      break;
    default:
      ThrowRuntimeError("unsupported function result type");
      break;
    }
    // create the ir function corresponding to the prototype
    llvm::Function *func =
        llvm::Function::Create(ft, llvm::Function::ExternalLinkage,
                               decl->getName(), m_theModule.get());
    // set names for all params
    auto &params = decl->getParams();
    unsigned idx = 0;
    for (auto &arg : func->args()) {
      arg.setName(params[idx++]->getName());
    }

    auto *compoundStmt = decl->getCompoundStmt();
    if (compoundStmt == nullptr) {
      return true;
    }
    llvm::BasicBlock *BB = llvm::BasicBlock::Create(*m_context, "entry", func);
    m_irBuilder->SetInsertPoint(BB);
    llvm::Value *bodyIr = getIr(compoundStmt);
    Assert(bodyIr != nullptr, decl, "function body ir not generated");
    m_irBuilder->CreateRet(bodyIr);
    // Validate the generated code, checking for consistency.
    llvm::verifyFunction(*func);

    m_astIrMap.insert({reinterpret_cast<std::uintptr_t>(decl), func});
    return true;
  }

  bool visitVarDecl(VarDecl *decl) {
    llvm::Value *v = nullptr;
    switch (decl->getType()->getKind()) {
    case Type::Kind::Integer:
      v = m_irBuilder->CreateAlloca(llvm::IntegerType::get(*m_context, 32),
                                    nullptr, decl->getName());
      break;
    case Type::Kind::Pointer:
      v = m_irBuilder->CreateAlloca(llvm::PointerType::get(*m_context, 0),
                                    nullptr, decl->getName());
      break;
    default:
      break;
    }

    if (v != nullptr) {
      m_astIrMap.insert({reinterpret_cast<std::uintptr_t>(decl), v});
    }
    return true;
  }

  bool visitParamDecl(ParamDecl *decl) { return true; }
  bool visitCompoundStmt(CompoundStmt *stmt) { return true; }
  bool visitDeclStmt(DeclStmt *stmt) { return true; }

  bool visitIfStmt(IfStmt *stmt) {
    Expr *cond = stmt->getCond();
    auto *condV = getIr(stmt->getCond());
    Assert(condV != nullptr, stmt, "cond ir not found");
    // Convert condition to a bool by comparing non-equal to 0.0.
    condV = m_irBuilder->CreateICmpEQ(
        condV, llvm::ConstantInt::get(*m_context, llvm::APInt(1, 0)), "ifcond");
    auto *func = m_irBuilder->GetInsertBlock()->getParent();
    llvm::BasicBlock *thenBB =
        llvm::BasicBlock::Create(*m_context, "then", func);
    llvm::BasicBlock *elseBB = nullptr;
    if (stmt->getElseStmt() != nullptr) {
      elseBB = llvm::BasicBlock::Create(*m_context, "else");
    }
    llvm::BasicBlock *mergeBB = llvm::BasicBlock::Create(*m_context, "ifcont");
    m_irBuilder->CreateCondBr(condV, thenBB, elseBB);

    // emit then block
    m_irBuilder->SetInsertPoint(thenBB);
    auto *thenV = getIr(stmt->getThenStmt());
    Assert(thenV != nullptr, stmt, "then ir not found");
    m_irBuilder->CreateBr(mergeBB);
    // thenBB = m_irBuilder->GetInsertBlock();

    // emit else block
    llvm::Value *elseV = nullptr;
    if (elseBB != nullptr) {
      m_irBuilder->SetInsertPoint(elseBB);
      elseV = getIr(stmt->getElseStmt());
      Assert(elseV != nullptr, stmt, "then ir not found");
      m_irBuilder->CreateBr(mergeBB);
      // elseBB = m_irBuilder->GetInsertBlock();
    }
    m_irBuilder->SetInsertPoint(mergeBB);
    llvm::PHINode *phi =
        m_irBuilder->CreatePHI(llvm::Type::getInt32Ty(*m_context), 2, "iftmp");
    phi->addIncoming(thenV, thenBB);
    phi->addIncoming(elseV, elseBB);

    m_astIrMap.insert({reinterpret_cast<std::uintptr_t>(stmt), phi});

    return true;
  }

  bool visitWhileStmt(WhileStmt *stmt) { return true; }
  bool visitContinueStmt(ContinueStmt *stmt) { return true; }
  bool visitBreakStmt(BreakStmt *stmt) { return true; }
  bool visitReturnStmt(ReturnStmt *stmt) {
    llvm::Value *retV = nullptr;
    if (stmt->getReturnExpr() == nullptr) {
      retV = m_irBuilder->CreateRetVoid();
    } else {
      auto *ir = getIr(stmt->getReturnExpr());
      Assert(ir != nullptr, stmt);
      retV = m_irBuilder->CreateRet(ir);
    }
    m_astIrMap.insert({reinterpret_cast<std::uintptr_t>(stmt), retV});
    return true;
  }
  bool visitConstant(Constant *expr) {
    llvm::Value *v =
        llvm::ConstantInt::get(*m_context, llvm::APInt(32, expr->getValue()));
    m_astIrMap.insert({reinterpret_cast<std::uintptr_t>(expr), v});
    return true;
  }

  bool visitStringLiteral(StringLiteral *expr) { return true; }

  bool visitBinaryExpr(BinaryExpr *expr) {
    llvm::Value *v{nullptr};
    auto *l = getIr(expr->getLeftOperand());
    auto *r = getIr(expr->getRightOperand());
    if (l == nullptr || r == nullptr) {
      throw std::runtime_error("operand ir empty");
    }
    switch (expr->getOperator()) {
    case Token::PLUS:
      v = m_irBuilder->CreateAdd(l, r);
      break;
    case Token::MINUS:
      v = m_irBuilder->CreateSub(l, r);
      break;
    case Token::STAR:
      v = m_irBuilder->CreateMul(l, r);
      break;
    case Token::SLASH:
      v = m_irBuilder->CreateSDiv(l, r);
      break;
    case Token::GT:
      v = m_irBuilder->CreateICmpSGT(l, r);
      break;
    case Token::GE:
      v = m_irBuilder->CreateICmpSGE(l, r);
      break;
    case Token::LT:
      v = m_irBuilder->CreateICmpSLT(l, r);
      break;
    case Token::LE:
      v = m_irBuilder->CreateICmpSLE(l, r);
      break;
    case Token::EQ:
      v = m_irBuilder->CreateICmpEQ(l, r);
      break;
    case Token::NEQ:
      v = m_irBuilder->CreateICmpNE(l, r);
      break;
    case Token::LOGIC_AND:
      v = m_irBuilder->CreateLogicalAnd(l, r);
      break;
    case Token::LOGIC_OR:
      v = m_irBuilder->CreateLogicalOr(l, r);
      break;
    // case Token::NOT:
    //   v = m_irBuilder->CreateNot(l, r);
    //   break;
    case Token::AND: // bitwise and

      v = m_irBuilder->CreateAnd(l, r);
      break;
    case Token::OR: // bitwise or
      v = m_irBuilder->CreateOr(l, r);
      break;
    // case Token::BIT_NOT:
    //   break;
    case Token::XOR:
      v = m_irBuilder->CreateXor(l, r);
      break;
    case Token::PERCENT:
      v = m_irBuilder->CreateSRem(l, r);
      break;
    case Token::LSHIFT:
      v = m_irBuilder->CreateShl(l, r);
      break;
    case Token::RSHIFT:
      v = m_irBuilder->CreateAShr(l, r);
      break;
    case Token::ASSIGN:
      v = m_irBuilder->CreateStore(l, r);
      break;
    default:
      break;
    }
    Assert(v != nullptr, expr, "binary expr ir empty");
    m_astIrMap.insert({reinterpret_cast<std::uintptr_t>(expr), v});
    return true;
  }
  bool visitUnaryExpr(UnaryExpr *expr) {
    llvm::Value *v{nullptr};
    auto *l = getIr(expr->getOperand());
    switch (expr->getOperator()) {
    case Token::LOGIC_NOT: {
      auto *zero = llvm::ConstantInt::get(*m_context, llvm::APInt(1, 0));
      v = m_irBuilder->CreateICmpNE(l, zero);
    } break;
    case Token::NOT:
      v = m_irBuilder->CreateNot(l);
      break;
    case Token::AND: // addressOf
      if (auto *declRef = llvm::dyn_cast<DeclRefExpr>(l)) {
        llvm::Value *ir = getIr(declRef->getRefDecl());
        Assert(ir != nullptr, expr, "referenced decl ir empty");
        v=ir;
      }

      break;
    case Token::STAR:
      // Assert(l)
      break;
    default:
      break;
    }
    return true;
  }
  bool visitCallExpr(CallExpr *expr) { return true; }
  bool visitCastExpr(CastExpr *expr) { return true; }
  bool visitDeclRefExpr(DeclRefExpr *expr) {

    // m_astIrMap.insert({reinterpret_cast<std::uintptr_t>(expr), v});
    return true;
  }
};
} // namespace rvlang