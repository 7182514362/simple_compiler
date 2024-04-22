#pragma once

#include "Ast.h"
#include "frontend/Decl.h"
#include "frontend/Expr.h"
#include "frontend/Stmt.h"

#include <llvm/Support/Casting.h>

namespace rvlang {
// preorder traverse ast tree
template <typename Derived> class AstVisitor {
protected:
  Derived &getDerived() { return *static_cast<Derived *>(this); }

  enum class TraverseOrder { PreOrder, PostOrder };

  TraverseOrder m_traverseOrder;

public:
  AstVisitor() : m_traverseOrder(TraverseOrder::PreOrder) {}
  virtual ~AstVisitor() {}

  void setTraverseOrder(TraverseOrder order) { m_traverseOrder = order; }

  bool isPreOrder() const { return m_traverseOrder == TraverseOrder::PreOrder; }
  bool isPostOrder() const {
    return m_traverseOrder == TraverseOrder::PostOrder;
  }

  // dispatch Decl
  bool TraverseDecl(Decl *decl) {
    switch (decl->getKind()) {
    case Decl::DeclKind::TranslationUnitDecl:
      if (!getDerived().TraverseTranslationUnitDecl(
              static_cast<TranslationUnitDecl *>(decl))) {
        return false;
      }
      break;
    case Decl::DeclKind::FunctionDecl:
      if (!getDerived().TraverseFunctionDecl(
              static_cast<FunctionDecl *>(decl))) {
        return false;
      }
      break;
    case Decl::DeclKind::VarDecl:
      if (!getDerived().TraverseVarDecl(static_cast<VarDecl *>(decl))) {
        return false;
      }
      break;
    case Decl::DeclKind::ParamDecl:
      if (!getDerived().TraverseParamDecl(static_cast<ParamDecl *>(decl))) {
        return false;
      }
      break;
    case Decl::DeclKind::ArrayDecl:
      if (!getDerived().TraverseArrayDecl(static_cast<ArrayDecl *>(decl))) {
        return false;
      }
      break;
    default:
      return false;
      break;
    }
    return true;
  }

  // dispatch Stmt
  bool TraverseStmt(Stmt *stmt) {
    if (stmt == nullptr) {
      return false;
    }
    switch (stmt->getKind()) {
    case Stmt::StmtKind::DeclStmt:
      if (!getDerived().TraverseDeclStmt(static_cast<DeclStmt *>(stmt))) {
        return false;
      }
      break;
    case Stmt::StmtKind::IfStmt:
      if (!getDerived().TraverseIfStmt(static_cast<IfStmt *>(stmt))) {
        return false;
      }
      break;
    case Stmt::StmtKind::WhileStmt:
      if (!getDerived().TraverseWhileStmt(static_cast<WhileStmt *>(stmt))) {
        return false;
      }
      break;
    case Stmt::StmtKind::CompoundStmt:
      if (!getDerived().TraverseCompoundStmt(
              static_cast<CompoundStmt *>(stmt))) {
        return false;
      }
      break;
    case Stmt::StmtKind::BreakStmt:
      if (!getDerived().TraverseBreakStmt(static_cast<BreakStmt *>(stmt))) {
        return false;
      }
      break;
    case Stmt::StmtKind::ContinueStmt:
      if (!getDerived().TraverseContinueStmt(
              static_cast<ContinueStmt *>(stmt))) {
        return false;
      }
      break;
    case Stmt::StmtKind::ReturnStmt:
      if (!getDerived().TraverseReturnStmt(static_cast<ReturnStmt *>(stmt))) {
        return false;
      }
      break;
    case Stmt::StmtKind::BinaryExpr:
      if (!getDerived().TraverseBinaryExpr(static_cast<BinaryExpr *>(stmt))) {
        return false;
      }
      break;
    case Stmt::StmtKind::UnaryExpr:
      if (!getDerived().TraverseUnaryExpr(static_cast<UnaryExpr *>(stmt))) {
        return false;
      }
      break;
    case Stmt::StmtKind::CallExpr:
      if (!getDerived().TraverseCallExpr(static_cast<CallExpr *>(stmt))) {
        return false;
      }
      break;
    case Stmt::StmtKind::CastExpr:
      if (!getDerived().TraverseCastExpr(static_cast<CastExpr *>(stmt))) {
        return false;
      }
      break;
    case Stmt::StmtKind::DeclRefExpr:
      if (!getDerived().TraverseDeclRefExpr(static_cast<DeclRefExpr *>(stmt))) {
        return false;
      }
      break;
    case Stmt::StmtKind::ArraySubscriptExpr:
      if (!getDerived().TraverseArraySubscriptExpr(
              static_cast<ArraySubscriptExpr *>(stmt))) {
        return false;
      }
      break;
    case Stmt::StmtKind::StringLiteral:
      if (!getDerived().TraverseStringLiteral(
              static_cast<StringLiteral *>(stmt))) {
        return false;
      }
      break;
    case Stmt::StmtKind::Constant:
      if (!getDerived().TraverseConstant(static_cast<Constant *>(stmt))) {
        return false;
      }
      break;
    default:
      return false;
      break;
    }
    return true;
  }

public:
  bool TraverseTranslationUnitDecl(TranslationUnitDecl *decl) {
    if (isPreOrder() && !getDerived().visitTranslationUnitDecl(decl)) {
      return false;
    }
    for (auto *d : decl->getDecls()) {
      if (!TraverseDecl(d)) {
        return false;
      }
    }
    if (isPostOrder() && !getDerived().visitTranslationUnitDecl(decl)) {
      return false;
    }
    return true;
  }

  bool TraverseFunctionDecl(FunctionDecl *decl) {
    if (isPreOrder() && !getDerived().visitFunctionDecl(decl)) {
      return false;
    }
    for (auto *param : decl->getParams()) {
      if (!getDerived().TraverseDecl(param)) {
        return false;
      }
    }
    auto *body = decl->getCompoundStmt();
    if (body != nullptr) {
      if (!getDerived().TraverseStmt(body)) {
        return false;
      }
    }
    if (isPostOrder() && !getDerived().visitFunctionDecl(decl)) {
      return false;
    }
    return true;
  }
  bool TraverseVarDecl(VarDecl *decl) {
    if (isPreOrder() && !getDerived().visitVarDecl(decl)) {
      return false;
    }
    if (decl->getInitExpr() != nullptr) {
      if (!TraverseStmt(decl->getInitExpr())) {
        return false;
      }
    }
    if (isPostOrder() && !getDerived().visitVarDecl(decl)) {
      return false;
    }
    return true;
  }
  bool TraverseParamDecl(ParamDecl *decl) {
    if (!getDerived().visitParamDecl(decl)) {
      return false;
    }
    return true;
  }
  bool TraverseArrayDecl(ArrayDecl *decl) {
    if (!getDerived().visitArrayDecl(decl)) {
      return false;
    }
    return true;
  }

public:
  bool TraverseConstant(Constant *stmt) {
    if (!getDerived().visitConstant(stmt)) {
      return false;
    }
    return true;
  }
  bool TraverseStringLiteral(StringLiteral *stmt) {
    if (!getDerived().visitStringLiteral(stmt)) {
      return false;
    }
    return true;
  }
  bool TraverseBinaryExpr(BinaryExpr *stmt) {
    if (isPreOrder() && !getDerived().visitBinaryExpr(stmt)) {
      return false;
    }
    if (!TraverseStmt(stmt->getLeftOperand())) {
      return false;
    }
    if (!TraverseStmt(stmt->getRightOperand())) {
      return false;
    }
    if (isPostOrder() && !getDerived().visitBinaryExpr(stmt)) {
      return false;
    }
    return true;
  }
  bool TraverseUnaryExpr(UnaryExpr *stmt) {
    if (isPreOrder() && !getDerived().visitUnaryExpr(stmt)) {
      return false;
    }
    if (!TraverseStmt(stmt->getOperand())) {
      return false;
    }
    if (isPostOrder() && !getDerived().visitUnaryExpr(stmt)) {
      return false;
    }
    return true;
  }
  bool TraverseCallExpr(CallExpr *stmt) {
    if (isPreOrder() && !getDerived().visitCallExpr(stmt)) {
      return false;
    }
    if (stmt->getDeclRefExpr() != nullptr &&
        !TraverseStmt(stmt->getDeclRefExpr())) {
      return false;
    }
    for (auto *param : stmt->getParams()) {
      if (!TraverseStmt(param)) {
        return false;
      }
    }
    if (isPostOrder() && !getDerived().visitCallExpr(stmt)) {
      return false;
    }
    return true;
  }
  bool TraverseCastExpr(CastExpr *expr) {
    if (isPreOrder() && !getDerived().visitCastExpr(expr)) {
      return false;
    }
    if (!TraverseStmt(expr->getOperand())) {
      return false;
    }
    if (isPostOrder() && !getDerived().visitCastExpr(expr)) {
      return false;
    }
    return true;
  }
  bool TraverseDeclRefExpr(DeclRefExpr *expr) {
    if (!getDerived().visitDeclRefExpr(expr)) {
      return false;
    }
    return true;
  }
  bool TraverseArraySubscriptExpr(ArraySubscriptExpr *expr) {
    if (isPreOrder() && !getDerived().visitArraySubscriptExpr(expr)) {
      return false;
    }
    if (!TraverseStmt(expr->getArrayDeclRef())) {
      return false;
    }
    if (!TraverseStmt(expr->getIndexExpr())) {
      return false;
    }
    if (isPostOrder() && !getDerived().visitArraySubscriptExpr(expr)) {
      return false;
    }
    return true;
  }
  bool TraverseCompoundStmt(CompoundStmt *stmt) {
    if (isPreOrder() && !getDerived().visitCompoundStmt(stmt)) {
      return false;
    }
    for (auto *s : stmt->getStmts()) {
      if (!TraverseStmt(s)) {
        return false;
      }
    }
    if (isPostOrder() && !getDerived().visitCompoundStmt(stmt)) {
      return false;
    }
    return true;
  }
  bool TraverseDeclStmt(DeclStmt *stmt) {
    if (isPreOrder() && !getDerived().visitDeclStmt(stmt)) {
      return false;
    }
    if (stmt->getDecl() != nullptr && !TraverseDecl(stmt->getDecl())) {
      return false;
    }
    if (isPostOrder() && !getDerived().visitDeclStmt(stmt)) {
      return false;
    }
    return true;
  }

  bool TraverseIfStmt(IfStmt *stmt) {
    if (isPreOrder() && !getDerived().visitIfStmt(stmt)) {
      return false;
    }
    if (!TraverseStmt(stmt->getCond())) {
      return false;
    }
    if (!TraverseStmt(stmt->getThenStmt())) {
      return false;
    }
    if (stmt->getElseStmt() != nullptr && !TraverseStmt(stmt->getElseStmt())) {
      return false;
    }
    if (isPostOrder() && !getDerived().visitIfStmt(stmt)) {
      return false;
    }
    return true;
  }
  bool TraverseWhileStmt(WhileStmt *stmt) {
    if (isPreOrder() && !getDerived().visitWhileStmt(stmt)) {
      return false;
    }
    if (!TraverseStmt(stmt->getCond())) {
      return false;
    }
    if (stmt->getCompoundStmt() != nullptr &&
        !TraverseStmt(stmt->getCompoundStmt())) {
      return false;
    }
    if (isPostOrder() && !getDerived().visitWhileStmt(stmt)) {
      return false;
    }
    return true;
  }
  bool TraverseContinueStmt(ContinueStmt *stmt) {
    if (!getDerived().visitContinueStmt(stmt)) {
      return false;
    }
    return true;
  }
  bool TraverseBreakStmt(BreakStmt *stmt) {
    if (!getDerived().visitBreakStmt(stmt)) {
      return false;
    }
    return true;
  }
  bool TraverseReturnStmt(ReturnStmt *stmt) {
    if (isPreOrder() && !getDerived().visitReturnStmt(stmt)) {
      return false;
    }
    if (stmt->getReturnExpr() != nullptr &&
        !TraverseStmt(stmt->getReturnExpr())) {
      return false;
    }
    if (isPostOrder() && !getDerived().visitReturnStmt(stmt)) {
      return false;
    }
    return true;
  }

public:
  bool visitTranslationUnitDecl(TranslationUnitDecl *decl) { return true; }
  bool visitFunctionDecl(FunctionDecl *decl) { return true; }
  bool visitVarDecl(VarDecl *decl) { return true; }
  bool visitParamDecl(ParamDecl *decl) { return true; }
  bool visitArrayDecl(ArrayDecl *decl) { return true; }
  bool visitCompoundStmt(CompoundStmt *stmt) { return true; }
  bool visitDeclStmt(DeclStmt *stmt) { return true; }
  bool visitIfStmt(IfStmt *stmt) { return true; }
  bool visitWhileStmt(WhileStmt *stmt) { return true; }
  bool visitContinueStmt(ContinueStmt *stmt) { return true; }
  bool visitBreakStmt(BreakStmt *stmt) { return true; }
  bool visitReturnStmt(ReturnStmt *stmt) { return true; }
  bool visitConstant(Constant *expr) { return true; }
  bool visitStringLiteral(StringLiteral *expr) { return true; }
  bool visitBinaryExpr(BinaryExpr *expr) { return true; }
  bool visitUnaryExpr(UnaryExpr *expr) { return true; }
  bool visitCallExpr(CallExpr *expr) { return true; }
  bool visitCastExpr(CastExpr *expr) { return true; }
  bool visitDeclRefExpr(DeclRefExpr *expr) { return true; }
  bool visitArraySubscriptExpr(ArraySubscriptExpr *expr) { return true; }
};
} // namespace rvlang