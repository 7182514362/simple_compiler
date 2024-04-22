#include "IREmiter.h"
#include "Common.h"
#include "frontend/Ast.h"
#include "frontend/Expr.h"
#include "frontend/Type.h"
#include <array>
#include <llvm/ADT/APInt.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/Casting.h>
#include <vector>

namespace rvlang {
llvm::Value *IREmiter::EmitFunctionDecl(FunctionDecl *decl) {
  enterScope();

  // create funtion prototype
  // for simplicity, param type only sypport 'int' and 'int*'
  std::vector<llvm::Type *> paramTypes;
  for (ParamDecl *param : decl->getParams()) {
    // llvm::Value *paramV = EmitDecl(param);
    // Assert(paramV, param, "ir empty");
    // paramTypes.push_back(paramV->getType());

    if (param->getType()->getKind() == Type::Kind::Integer) {
      paramTypes.push_back(llvm::Type::getInt32Ty(*m_context));
    } else if (param->getType()->getKind() == Type::Kind::Pointer) {
      auto *pt = llvm::dyn_cast<PointerType>(param->getType());
      Assert(pt != nullptr &&
                 pt->getPointeeType()->getKind() == Type::Kind::Integer,
             param, "");
      paramTypes.push_back(llvm::Type::getInt32PtrTy(*m_context));
    } else {
      Assert(false, param, "unsupported param type");
    }
  }
  // function return type only support 'int', 'int*' and 'void'
  llvm::FunctionType *ft = nullptr;
  switch (decl->getRetType()->getKind()) {
  case Type::Kind::Integer:
    ft = llvm::FunctionType::get(llvm::Type::getInt32Ty(*m_context), paramTypes,
                                 false);
    break;
  case Type::Kind::Void:
    ft = llvm::FunctionType::get(llvm::Type::getVoidTy(*m_context), paramTypes,
                                 false);
    break;
  case Type::Kind::Pointer:
    if (llvm::dyn_cast<PointerType>(decl->getRetType())
            ->getPointeeType()
            ->getKind() != Type::Kind::Integer) {
      ThrowRuntimeError("unsupported function result type");
    }
    ft = llvm::FunctionType::get(llvm::Type::getInt32PtrTy(*m_context),
                                 paramTypes, false);
    break;
  default:
    ThrowRuntimeError("unsupported function result type");
    break;
  }
  // create the ir function corresponding to the prototype
  llvm::Function *func = llvm::Function::Create(
      ft, llvm::Function::ExternalLinkage, decl->getName(), *m_theModule);
  // set names for all params
  auto &params = decl->getParams();
  unsigned idx = 0;
  for (auto &arg : func->args()) {
    arg.setName(params[idx++]->getName());
  }

  auto *compoundStmt = decl->getCompoundStmt();
  if (compoundStmt == nullptr) {
    return func;
  }
  llvm::BasicBlock *entryBB =
      llvm::BasicBlock::Create(*m_context, "entry", func);
  m_irBuilder->SetInsertPoint(entryBB);
  // allocate param
  int i = 0;
  for (ParamDecl *param : decl->getParams()) {
    // EmitDecl(param);
    auto *paramV = m_irBuilder->CreateAlloca(m_irBuilder->getInt32Ty(), nullptr,
                                             param->getName());
    m_irBuilder->CreateStore(func->getArg(i++), paramV);
    currentScope().insert({param->getName(), paramV});
  }
  // emit function body
  EmitCompoundStmt(compoundStmt, entryBB);
  entryBB = m_irBuilder->GetInsertBlock();

  // Validate the generated code, checking for consistency.
  llvm::verifyFunction(*func);
  leaveScope();

  // func->print(llvm::outs());

  return func;
}

llvm::Value *IREmiter::EmitVarDecl(VarDecl *decl) {
  llvm::AllocaInst *v = nullptr;
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
  if (auto *initExpr = decl->getInitExpr()) {
    auto *initIr = EmitStmt(initExpr);
    Assert(initIr, initExpr, "ir empty");

    m_irBuilder->CreateStore(initIr, v);
  }
  if (v != nullptr) {
    currentScope().insert({decl->getName(), v});
  }
  return v;
}

llvm::Value *IREmiter::EmitParamDecl(ParamDecl *decl) {
  // auto *func = m_irBuilder->GetInsertBlock()->getParent();
  // llvm::AllocaInst *v{nullptr};
  // // for simplicity, param type only sypport 'int' and 'int*'
  // if (decl->getType()->getKind() == Type::Kind::Integer) {
  //   auto *intType = llvm::Type::getInt32Ty(*m_context);

  //   v = m_irBuilder->CreateAlloca(intType, nullptr, decl->getName());

  //   // m_irBuilder->CreateStore(func->getA, Value *Ptr)

  // } else if (decl->getType()->getKind() == Type::Kind::Pointer) {
  //   if (llvm::dyn_cast<PointerType>(decl->getType())
  //           ->getPointeeType()
  //           ->getKind() != Type::Kind::Integer) {
  //     ThrowRuntimeError("unsupported prarm type");
  //   }
  //   auto *intPtrType = llvm::Type::getInt32PtrTy(*m_context);
  //   v = m_irBuilder->CreateAlloca(intPtrType, nullptr, decl->getName());
  // } else {
  //   ThrowRuntimeError("unsupported prarm type");
  //   return nullptr;
  // }
  // currentScope().insert({decl->getName(), v});
  // return v;

  return nullptr;
}

llvm::Value *IREmiter::EmitArrayDecl(ArrayDecl *decl) {

  // if global

  llvm::IntegerType *intType = llvm::Type::getInt32Ty(*m_context);
  llvm::PointerType *intPtrTy = llvm::Type::getInt32PtrTy(*m_context);
  llvm::ArrayType *arrayType = llvm::ArrayType::get(intType, decl->getLength());

  std::vector<llvm::Constant *> elements;
  for (auto element : decl->getElements()) {
    elements.push_back(m_irBuilder->getInt32(element));
  }

  llvm::Constant *constArray{nullptr};
  if (decl->getElementType()->getKind() == Type::Kind::Integer) {
    constArray = llvm::ConstantArray::get(
        llvm::ArrayType::get(intType, decl->getElements().size()), elements);
    arrayType = llvm::ArrayType::get(intType, decl->getLength());
  } else if (decl->getElementType()->getKind() == Type::Kind::Pointer) {
    auto *pt = llvm::dyn_cast<PointerType>(decl->getElementType());
    Assert(pt->getPointeeType()->getKind() == Type::Kind::Integer, decl,
           "only int* supported");

    auto *intPtrType = llvm::Type::getInt32PtrTy(*m_context);

    constArray = llvm::ConstantArray::get(
        llvm::ArrayType::get(intPtrType, decl->getElements().size()), elements);

    arrayType = llvm::ArrayType::get(intPtrType, decl->getLength());
  }

  Assert(arrayType, decl, "only int/int* supported");

  m_theModule->getOrInsertGlobal(decl->getName(), arrayType);

  llvm::GlobalVariable *gv = m_theModule->getNamedGlobal(decl->getName());
  gv->setInitializer(constArray);
  gv->setLinkage(llvm::GlobalValue::PrivateLinkage);

  // auto *globalVar = new llvm::GlobalVariable(*m_theModule, arrayType, true,
  //                                            llvm::GlobalValue::PrivateLinkage,
  //                                            constArray, decl->getName());

  return gv;

  // auto *intType = m_irBuilder->getInt32Ty();
  // llvm::Value *sizeV = llvm::ConstantInt::get(*m_context, llvm::APInt(32,
  // 0)); llvm::AllocaInst *v{nullptr}; if (decl->getElementType()->getKind() ==
  // Type::Kind::Integer) {
  //   v = m_irBuilder->CreateAlloca(intType, sizeV, decl->getName());
  // } else if (decl->getElementType()->getKind() == Type::Kind::Pointer) {
  //   auto *pt = llvm::dyn_cast<PointerType>(decl->getElementType());
  //   Assert(pt->getPointeeType()->getKind() == Type::Kind::Integer, decl,
  //          "only int* supported");
  //   v = m_irBuilder->CreateAlloca(llvm::Type::getInt32PtrTy(*m_context),
  //   sizeV,
  //                                 decl->getName());
  // }
  // if (v != nullptr) {
  //   currentScope().insert({decl->getName(), v});
  // }
  // return v;
}

llvm::Value *IREmiter::EmitStringLiteral(StringLiteral *stmt) {
  return nullptr;
}

llvm::Value *IREmiter::EmitBinaryExpr(BinaryExpr *expr) {
  llvm::Value *v{nullptr};
  auto *l = EmitStmt(expr->getLeftOperand());
  auto *lp = l;
  Assert(l != nullptr, expr->getLeftOperand(), "ir empty");

  auto *r = EmitStmt(expr->getRightOperand());
  Assert(r != nullptr, expr->getRightOperand(), "ir empty");

  if (l == nullptr || r == nullptr) {
    throw std::runtime_error("operand ir empty");
  }
  switch (expr->getOperator()) {
  case Token::PLUS:
    l = loadAllocaValue(l);
    r = loadAllocaValue(r);
    v = m_irBuilder->CreateAdd(l, r);
    break;
  case Token::MINUS:
    l = loadAllocaValue(l);
    r = loadAllocaValue(r);
    v = m_irBuilder->CreateSub(l, r);
    break;
  case Token::STAR:
    l = loadAllocaValue(l);
    r = loadAllocaValue(r);
    v = m_irBuilder->CreateMul(l, r);
    break;
  case Token::SLASH:
    l = loadAllocaValue(l);
    r = loadAllocaValue(r);
    v = m_irBuilder->CreateSDiv(l, r);
    break;
  case Token::GT:
    l = loadAllocaValue(l);
    r = loadAllocaValue(r);
    v = m_irBuilder->CreateICmpSGT(l, r);
    break;
  case Token::GE:
    l = loadAllocaValue(l);
    r = loadAllocaValue(r);
    v = m_irBuilder->CreateICmpSGE(l, r);
    break;
  case Token::LT:
    l = loadAllocaValue(l);
    r = loadAllocaValue(r);
    v = m_irBuilder->CreateICmpSLT(l, r);
    break;
  case Token::LE:
    l = loadAllocaValue(l);
    r = loadAllocaValue(r);
    v = m_irBuilder->CreateICmpSLE(l, r);
    break;
  case Token::EQ:
    l = loadAllocaValue(l);
    r = loadAllocaValue(r);
    v = m_irBuilder->CreateICmpEQ(l, r);
    break;
  case Token::NEQ:
    l = loadAllocaValue(l);
    r = loadAllocaValue(r);
    v = m_irBuilder->CreateICmpNE(l, r);
    break;
  case Token::LOGIC_AND:
    l = loadAllocaValue(l);
    r = loadAllocaValue(r);
    v = m_irBuilder->CreateLogicalAnd(l, r);
    break;
  case Token::LOGIC_OR:
    l = loadAllocaValue(l);
    r = loadAllocaValue(r);
    v = m_irBuilder->CreateLogicalOr(l, r);
    break;
  // case Token::NOT:
  //   v = m_irBuilder->CreateNot(l, r);
  //   break;
  case Token::AND: // bitwise and
    l = loadAllocaValue(l);
    r = loadAllocaValue(r);
    v = m_irBuilder->CreateAnd(l, r);
    break;
  case Token::OR: // bitwise or
    l = loadAllocaValue(l);
    r = loadAllocaValue(r);
    v = m_irBuilder->CreateOr(l, r);
    break;
  // case Token::BIT_NOT:
  //   break;
  case Token::XOR:
    l = loadAllocaValue(l);
    r = loadAllocaValue(r);
    v = m_irBuilder->CreateXor(l, r);
    break;
  case Token::PERCENT:
    l = loadAllocaValue(l);
    r = loadAllocaValue(r);
    v = m_irBuilder->CreateSRem(l, r);
    break;
  case Token::LSHIFT:
    l = loadAllocaValue(l);
    r = loadAllocaValue(r);
    v = m_irBuilder->CreateShl(l, r);
    break;
  case Token::RSHIFT:
    l = loadAllocaValue(l);
    r = loadAllocaValue(r);
    v = m_irBuilder->CreateAShr(l, r);
    break;
  case Token::ASSIGN:
    // left operand must be a lvalue
    Assert(l->getType()->isPointerTy(), expr->getLeftOperand());
    r = loadAllocaValue(r);
    v = m_irBuilder->CreateStore(r, l);
    break;
  default:
    break;
  }
  Assert(v != nullptr, expr, "binary expr ir empty");
  return v;
}

llvm::Value *IREmiter::EmitUnaryExpr(UnaryExpr *expr) {
  llvm::Value *v{nullptr};
  auto *operandV = EmitStmt(expr->getOperand());
  Assert(operandV != nullptr, expr->getOperand(), "ir empty");

  switch (expr->getOperator()) {
  case Token::LOGIC_NOT: {
    operandV = loadAllocaValue(operandV);
    v = m_irBuilder->CreateICmpNE(operandV, m_irBuilder->getInt32(0));
  } break;
  case Token::NOT:
    operandV = loadAllocaValue(operandV);
    v = m_irBuilder->CreateNot(operandV);
    break;
  case Token::AND: // addressOf
  {
    auto *declRef = llvm::dyn_cast<DeclRefExpr>(expr->getOperand());
    Assert(declRef != nullptr, expr->getOperand(), "ir empty");

    llvm::Value *ir = EmitStmt(declRef);
    Assert(ir != nullptr, expr->getOperand(), "ir empty");
    v = ir;
  } break;
  case Token::STAR: {
    auto *operand = expr->getOperand();
    Assert(operand->getType()->getKind() == Type::Kind::Pointer, operand,
           "not a pointer");
    auto *pt = llvm::dyn_cast<PointerType>(operand->getType());
    Assert(pt->getPointeeType()->getKind() == Type::Kind::Integer, operand,
           "not a int pointer");
    // v = m_irBuilder->CreateLoad(m_irBuilder->getInt32Ty(), operandV);
    v = operandV;
  } break;
  default:
    break;
  }
  return v;
}

llvm::Value *IREmiter::EmitCallExpr(CallExpr *stmt) {

  auto *callee = m_theModule->getFunction(stmt->getDeclRefExpr()->getRefName());
  std::vector<llvm::Value *> args;
  for (auto *param : stmt->getParams()) {
    auto *paramV = EmitStmt(param);
    Assert(paramV, param, "ir empty");
    args.push_back(paramV);
  }
  return m_irBuilder->CreateCall(callee, args);
}

llvm::Value *IREmiter::EmitCastExpr(CastExpr *expr) {

  auto *fromV = EmitStmt(expr->getOperand());
  Assert(fromV, expr->getOperand(), "ir empty");

  return m_irBuilder->CreateCast(llvm::Instruction::SExt, fromV,
                                 llvm::Type::getInt32Ty(*m_context));
}

llvm::Value *IREmiter::EmitDeclRefExpr(DeclRefExpr *expr) {
  auto *decl = expr->getRefDecl();
  switch (decl->getKind()) {
  case Decl::DeclKind::ParamDecl:
    if (llvm::AllocaInst *v = getNamedValue(decl->getName())) {
      // return m_irBuilder->CreateLoad(v->getAllocatedType(), v);
      return v;
    }
    break;
  case Decl::DeclKind::VarDecl:
    if (llvm::AllocaInst *v = getNamedValue(decl->getName())) {
      // return m_irBuilder->CreateLoad(v->getAllocatedType(), v);
      return v;
    }
    break;
  case Decl::DeclKind::ArrayDecl:
    if (auto *v = m_theModule->getNamedValue(decl->getName())) {
      return v;
    }
    break;
  case Decl::DeclKind::FunctionDecl:
    if (auto *func = m_theModule->getFunction(expr->getRefName())) {
      return func;
    }
    break;
  default:
    break;
  }
  Assert(false, expr, "Decl ir not found: " + decl->getName());
  return nullptr;
}

llvm::Value *IREmiter::EmitArraySubscriptExpr(ArraySubscriptExpr *expr) {
  auto *declRefExpr = llvm::dyn_cast<DeclRefExpr>(expr->getArrayDeclRef());
  Assert(declRefExpr, declRefExpr, "");

  auto *idxV = EmitStmt(expr->getIndexExpr());
  Assert(idxV != nullptr, expr, "ir empty");

  if (llvm::AllocaInst *v = getNamedValue(declRefExpr->getRefName())) {
    // return m_irBuilder->CreateGEP(v->getAllocatedType(), v, idxV);
    return m_irBuilder->CreateInBoundsGEP(v->getAllocatedType(), v, idxV);
  } else if (llvm::GlobalVariable *gv =
                 m_theModule->getNamedGlobal(declRefExpr->getRefName())) {

    std::array<llvm::Value *, 2> idxes{m_irBuilder->getInt32(0), idxV};
    auto *elemPtr = m_irBuilder->CreateGEP(gv->getValueType(), gv, idxes);
    // if this is a rvalue, load it's value
    // else return element ptr
    return m_irBuilder->CreateLoad(m_irBuilder->getInt32Ty(), elemPtr);

    // auto *elemPtr = m_irBuilder->CreateInBoundsGEP(
    //     gv->getValueType()->getArrayElementType(), gv, idxes);
    // return m_irBuilder->CreateLoad(m_irBuilder->getInt32Ty(), elemPtr);

    // return m_irBuilder->CreateExtractElement(gv, idxV);
  }

  Assert(false, expr, "ir empty");
  return nullptr;
}

llvm::Value *IREmiter::EmitCompoundStmt(CompoundStmt *stmt,
                                        llvm::BasicBlock *bb) {
  enterScope();
  if (bb == nullptr) {
    auto *func = m_irBuilder->GetInsertBlock()->getParent();
    bb = llvm::BasicBlock::Create(*m_context, "compound", func);
    m_irBuilder->CreateBr(bb);
    m_irBuilder->SetInsertPoint(bb);
  }

  for (auto *st : stmt->getStmts()) {
    auto *v = EmitStmt(st);
    Assert(v, st, "ir empty");
  }
  leaveScope();
  return bb;
}

llvm::Value *IREmiter::EmitDeclStmt(DeclStmt *stmt) {
  return EmitDecl(stmt->getDecl());
}

llvm::Value *IREmiter::EmitIfStmt(IfStmt *stmt) {
  Expr *cond = stmt->getCond();

  auto *condV = EmitStmt(stmt->getCond());
  Assert(condV != nullptr, stmt, "ir empty");
  llvm::Type *intType = m_irBuilder->getInt32Ty();

  // Convert condition to a bool by comparing non-equal to 0.0.

  // condV = m_irBuilder->CreateICmpEQ(condV, m_irBuilder->getInt32(0),
  // "if.cond");
  auto *func = m_irBuilder->GetInsertBlock()->getParent();
  llvm::BasicBlock *thenBB =
      llvm::BasicBlock::Create(*m_context, "if.then", func);

  llvm::BasicBlock *mergeBB =
      llvm::BasicBlock::Create(*m_context, "merge", func);

  llvm::BasicBlock *elseBB = nullptr;
  if (stmt->getElseStmt() != nullptr) {
    elseBB = llvm::BasicBlock::Create(*m_context, "if.else", func);
    m_irBuilder->CreateCondBr(condV, thenBB, elseBB);
  } else {
    m_irBuilder->CreateCondBr(condV, thenBB, mergeBB);
  }

  // emit then block
  m_irBuilder->SetInsertPoint(thenBB);
  EmitCompoundStmt(stmt->getThenStmt(), thenBB);
  m_irBuilder->CreateBr(mergeBB);
  thenBB = m_irBuilder->GetInsertBlock();

  // emit else block
  if (elseBB != nullptr) {
    m_irBuilder->SetInsertPoint(elseBB);
    EmitCompoundStmt(stmt->getElseStmt(), elseBB);
    m_irBuilder->CreateBr(mergeBB);
    elseBB = m_irBuilder->GetInsertBlock();
  }
  m_irBuilder->SetInsertPoint(mergeBB);

  return mergeBB;
}

llvm::Value *IREmiter::EmitWhileStmt(WhileStmt *stmt) {

  auto *func = m_irBuilder->GetInsertBlock()->getParent();

  llvm::BasicBlock *condBB =
      llvm::BasicBlock::Create(*m_context, "while.cond", func);
  m_irBuilder->CreateBr(condBB);
  m_irBuilder->SetInsertPoint(condBB);
  auto *condV = EmitStmt(stmt->getCond());
  Assert(condV != nullptr, stmt, "ir empty");
  // condV = m_irBuilder->CreateICmpEQ(
  //     condV, llvm::ConstantInt::get(*m_context, llvm::APInt(1, 0)),
  //     "if.cond");

  llvm::BasicBlock *trueBB =
      llvm::BasicBlock::Create(*m_context, "while.true", func);
  llvm::BasicBlock *falseBB =
      llvm::BasicBlock::Create(*m_context, "while.false", func);
  m_irBuilder->CreateCondBr(condV, trueBB, falseBB);

  m_irBuilder->SetInsertPoint(trueBB);
  EmitCompoundStmt(stmt->getCompoundStmt(), trueBB);

  m_irBuilder->SetInsertPoint(falseBB);

  return falseBB;
}

llvm::Value *IREmiter::EmitContinueStmt(ContinueStmt *stmt) {
  // ???????
  return m_irBuilder->CreateBr(m_irBuilder->GetInsertBlock());
}

llvm::Value *IREmiter::EmitBreakStmt(BreakStmt *stmt) {

  // ???????
  return m_irBuilder->CreateBr(m_irBuilder->GetInsertBlock());
}

llvm::Value *IREmiter::EmitReturnStmt(ReturnStmt *stmt) {
  llvm::Value *v = nullptr;
  if (stmt->getReturnExpr() == nullptr) {
    v = m_irBuilder->CreateRetVoid();
  } else {
    auto *ir = EmitStmt(stmt->getReturnExpr());
    Assert(ir != nullptr, stmt);
    v = m_irBuilder->CreateRet(ir);
  }
  return v;
}

} // namespace rvlang