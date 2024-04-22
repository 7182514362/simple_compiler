#pragma once

#include "Ast.h"
#include "frontend/Decl.h"
#include "frontend/Expr.h"
#include "frontend/Stmt.h"

#include <llvm/ADT/APInt.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DebugInfoMetadata.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Operator.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Use.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/Casting.h>
#include <llvm/Support/raw_ostream.h>
#include <map>
#include <vector>

namespace rvlang {
// template <typename Derived>
class IREmiter {
protected:
  // Derived &getDerived() { return *static_cast<Derived *>(this); }

  std::unique_ptr<llvm::LLVMContext> m_context;
  std::unique_ptr<llvm::IRBuilder<>> m_irBuilder;
  std::unique_ptr<llvm::Module> m_theModule;
  // std::map<std::string, llvm::Value *> m_namedValues;

  using NamedValueScope = std::map<std::string, llvm::AllocaInst *>;

  std::vector<NamedValueScope> m_scopeChain;

private:
  NamedValueScope &currentScope() { return m_scopeChain.back(); }
  void enterScope() { m_scopeChain.emplace_back(); }
  void leaveScope() { m_scopeChain.pop_back(); }

  llvm::AllocaInst *getNamedValue(const std::string &name) {
    for (auto itor = m_scopeChain.rbegin(); itor != m_scopeChain.rend();
         ++itor) {
      auto it = itor->find(name);
      if (it != itor->end()) {
        return it->second;
      }
    }
    return nullptr;
  }

public:
  IREmiter()
      : m_context(std::make_unique<llvm::LLVMContext>()),
        m_irBuilder(std::make_unique<llvm::IRBuilder<>>(*m_context)),
        m_theModule(
            std::make_unique<llvm::Module>("example module", *m_context)) {}
  virtual ~IREmiter() = default;

  llvm::Value *EmitDecl(Decl *decl) {
    switch (decl->getKind()) {
    case Decl::DeclKind::TranslationUnitDecl:
      return EmitTranslationUnitDecl(static_cast<TranslationUnitDecl *>(decl));
      break;
    case Decl::DeclKind::FunctionDecl:
      return EmitFunctionDecl(static_cast<FunctionDecl *>(decl));
      break;
    case Decl::DeclKind::VarDecl:
      return EmitVarDecl(static_cast<VarDecl *>(decl));
      break;
    case Decl::DeclKind::ParamDecl:
      return EmitParamDecl(static_cast<ParamDecl *>(decl));
      break;
    case Decl::DeclKind::ArrayDecl:
      return EmitArrayDecl(static_cast<ArrayDecl *>(decl));
      break;
    default:
      return nullptr;
      break;
    }
    return nullptr;
  }

  llvm::Value *EmitStmt(Stmt *stmt) {
    if (stmt == nullptr) {
      return nullptr;
    }
    switch (stmt->getKind()) {
    case Stmt::StmtKind::DeclStmt:
      return EmitDeclStmt(static_cast<DeclStmt *>(stmt));
      break;
    case Stmt::StmtKind::IfStmt:
      return EmitIfStmt(static_cast<IfStmt *>(stmt));
      break;
    case Stmt::StmtKind::WhileStmt:
      return EmitWhileStmt(static_cast<WhileStmt *>(stmt));
      break;
    case Stmt::StmtKind::CompoundStmt:
      return EmitCompoundStmt(static_cast<CompoundStmt *>(stmt));
      break;
    case Stmt::StmtKind::BreakStmt:
      return EmitBreakStmt(static_cast<BreakStmt *>(stmt));
      break;
    case Stmt::StmtKind::ContinueStmt:
      return EmitContinueStmt(static_cast<ContinueStmt *>(stmt));
      break;
    case Stmt::StmtKind::ReturnStmt:
      return EmitReturnStmt(static_cast<ReturnStmt *>(stmt));
      break;
    case Stmt::StmtKind::BinaryExpr:
      return EmitBinaryExpr(static_cast<BinaryExpr *>(stmt));
      break;
    case Stmt::StmtKind::UnaryExpr:
      return EmitUnaryExpr(static_cast<UnaryExpr *>(stmt));
      break;
    case Stmt::StmtKind::CallExpr:
      return EmitCallExpr(static_cast<CallExpr *>(stmt));
      break;
    case Stmt::StmtKind::CastExpr:
      return EmitCastExpr(static_cast<CastExpr *>(stmt));
      break;
    case Stmt::StmtKind::DeclRefExpr:
      return EmitDeclRefExpr(static_cast<DeclRefExpr *>(stmt));
      break;
    case Stmt::StmtKind::ArraySubscriptExpr:
      return EmitArraySubscriptExpr(static_cast<ArraySubscriptExpr *>(stmt));
      break;
    case Stmt::StmtKind::StringLiteral:
      return EmitStringLiteral(static_cast<StringLiteral *>(stmt));
      break;
    case Stmt::StmtKind::Constant:
      return EmitConstant(static_cast<Constant *>(stmt));
      break;
    default:
      break;
    }
    return nullptr;
  }

public:
  llvm::Value *EmitTranslationUnitDecl(TranslationUnitDecl *decl) {
    m_scopeChain.emplace_back();
    // visitTranslationUnitDecl(decl);
    for (auto *d : decl->getDecls()) {
      EmitDecl(d);
    }
    m_theModule->print(llvm::outs(), nullptr);
    return nullptr;
  }

  llvm::Value *EmitFunctionDecl(FunctionDecl *decl);
  llvm::Value *EmitVarDecl(VarDecl *decl);
  llvm::Value *EmitParamDecl(ParamDecl *decl);
  llvm::Value *EmitArrayDecl(ArrayDecl *decl);

public:
  llvm::Value *EmitConstant(Constant *expr) {
    return llvm::ConstantInt::get(*m_context,
                                  llvm::APInt(32, expr->getValue()));
  }
  llvm::Value *EmitStringLiteral(StringLiteral *stmt);
  llvm::Value *EmitBinaryExpr(BinaryExpr *stmt);
  llvm::Value *EmitUnaryExpr(UnaryExpr *stmt);
  llvm::Value *EmitCallExpr(CallExpr *stmt);
  llvm::Value *EmitCastExpr(CastExpr *expr);
  llvm::Value *EmitDeclRefExpr(DeclRefExpr *expr);
  llvm::Value *EmitArraySubscriptExpr(ArraySubscriptExpr *expr);
  llvm::Value *EmitCompoundStmt(CompoundStmt *stmt,
                                llvm::BasicBlock *bb = nullptr);
  llvm::Value *EmitDeclStmt(DeclStmt *stmt);

  llvm::Value *EmitIfStmt(IfStmt *stmt);
  llvm::Value *EmitWhileStmt(WhileStmt *stmt);
  llvm::Value *EmitContinueStmt(ContinueStmt *stmt);
  llvm::Value *EmitBreakStmt(BreakStmt *stmt);
  llvm::Value *EmitReturnStmt(ReturnStmt *stmt);

private:
  llvm::Value *loadAllocaValue(llvm::Value *v) {
    // if v is a local variable
    if (auto *allocaInst = llvm::dyn_cast<llvm::AllocaInst>(v)) {
      v = m_irBuilder->CreateLoad(allocaInst->getAllocatedType(), allocaInst);
    }
    return v;
  }
};
} // namespace rvlang