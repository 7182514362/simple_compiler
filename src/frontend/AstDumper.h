#pragma once

#include "frontend/AstVisitor.h"
#include "frontend/Decl.h"
#include "frontend/Token.h"

#include <cstdint>
#include <cstdio>
#include <iostream>
#include <type_traits>

namespace rvlang {
class AstDumper : public AstVisitor<AstDumper> {
private:
  int m_depth{0};
  std::ostream &m_ostream;

private:
  std::string indent() const { return std::string(m_depth * 2, ' '); }

  std::string ptrToString(void *p) const {
    char buf[32] = {0};
    std::sprintf(buf, "0x%lx", reinterpret_cast<std::uintptr_t>(p));
    return buf;
  }

  template <typename Node> std::string header(Node *node) {
    if constexpr (std::is_base_of_v<Decl, Node>) {
      return indent() + green() + std::string(node->getKindName()) + " " +
             yellow() + ptrToString(node) + " " + white();
    }
    if constexpr (std::is_base_of_v<Stmt, Node> &&
                  !std::is_base_of_v<Expr, Node>) {
      return indent() + red() + std::string(node->getKindName()) + " " +
             yellow() + ptrToString(node) + " " + white();
    }
    if constexpr (std::is_base_of_v<Expr, Node>) {
      return indent() + cyan() + std::string(node->getKindName()) + " " +
             yellow() + ptrToString(node) + " " + white();
    }
  }

public:
  bool TraverseTranslationUnitDecl(TranslationUnitDecl *decl) {
    if (!getDerived().visitTranslationUnitDecl(decl)) {
      return false;
    }
    ++m_depth;
    for (auto *d : decl->getDecls()) {
      if (!TraverseDecl(d)) {
        return false;
      }
    }
    --m_depth;
    return true;
  }

  bool TraverseFunctionDecl(FunctionDecl *decl) {
    if (!getDerived().visitFunctionDecl(decl)) {
      return false;
    }
    ++m_depth;
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
    --m_depth;
    return true;
  }

public:
  bool TraverseBinaryExpr(BinaryExpr *stmt) {
    if (!getDerived().visitBinaryExpr(stmt)) {
      return false;
    }
    ++m_depth;
    if (!TraverseStmt(stmt->getLeftOperand())) {
      return false;
    }
    if (!TraverseStmt(stmt->getRightOperand())) {
      return false;
    }
    --m_depth;
    return true;
  }
  bool TraverseUnaryExpr(UnaryExpr *stmt) {
    if (!getDerived().visitUnaryExpr(stmt)) {
      return false;
    }
    ++m_depth;
    if (!TraverseStmt(stmt->getOperand())) {
      return false;
    }
    --m_depth;
    return true;
  }
  bool TraverseCallExpr(CallExpr *stmt) {
    if (!getDerived().visitCallExpr(stmt)) {
      return false;
    }
    ++m_depth;
    if (stmt->getDeclRefExpr() != nullptr &&
        !TraverseStmt(stmt->getDeclRefExpr())) {
      return false;
    }
    for (auto *param : stmt->getParams()) {
      if (!TraverseStmt(param)) {
        return false;
      }
    }
    --m_depth;
    return true;
  }
  bool TraverseCastExpr(CastExpr *expr) {
    if (!getDerived().visitCastExpr(expr)) {
      return false;
    }
    ++m_depth;
    if (!TraverseStmt(expr->getOperand())) {
      return false;
    }
    --m_depth;
    return true;
  }

  bool TraverseArraySubscriptExpr(ArraySubscriptExpr *expr) {
    if (!getDerived().visitArraySubscriptExpr(expr)) {
      return false;
    }
    ++m_depth;
    if (!TraverseStmt(expr->getArrayDeclRef())) {
      return false;
    }
    if (!TraverseStmt(expr->getIndexExpr())) {
      return false;
    }
    --m_depth;
    return true;
  }
  bool TraverseCompoundStmt(CompoundStmt *stmt) {
    if (!getDerived().visitCompoundStmt(stmt)) {
      return false;
    }
    ++m_depth;
    for (auto *s : stmt->getStmts()) {
      if (!TraverseStmt(s)) {
        return false;
      }
    }
    --m_depth;
    return true;
  }
  bool TraverseDeclStmt(DeclStmt *stmt) {
    if (!getDerived().visitDeclStmt(stmt)) {
      return false;
    }
    ++m_depth;
    if (stmt->getDecl() != nullptr && !TraverseDecl(stmt->getDecl())) {
      return false;
    }
    --m_depth;
    return true;
  }
  bool TraverseIfStmt(IfStmt *stmt) {
    if (!getDerived().visitIfStmt(stmt)) {
      return false;
    }
    ++m_depth;
    if (!TraverseStmt(stmt->getCond())) {
      return false;
    }
    if (!TraverseStmt(stmt->getThenStmt())) {
      return false;
    }
    if (stmt->getElseStmt() != nullptr && !TraverseStmt(stmt->getElseStmt())) {
      return false;
    }
    --m_depth;
    return true;
  }

  bool TraverseWhileStmt(WhileStmt *stmt) {
    if (!getDerived().visitWhileStmt(stmt)) {
      return false;
    }
    ++m_depth;
    if (!TraverseStmt(stmt->getCond())) {
      return false;
    }
    if (stmt->getCompoundStmt() != nullptr &&
        !TraverseStmt(stmt->getCompoundStmt())) {
      return false;
    }
    --m_depth;
    return true;
  }
  bool TraverseReturnStmt(ReturnStmt *stmt) {
    if (!getDerived().visitReturnStmt(stmt)) {
      return false;
    }
    ++m_depth;
    if (stmt->getReturnExpr() != nullptr &&
        !TraverseStmt(stmt->getReturnExpr())) {
      return false;
    }
    --m_depth;
    return true;
  }

public:
  AstDumper() : m_ostream(std::cout) {}
  ~AstDumper() {}

  bool visitTranslationUnitDecl(TranslationUnitDecl *decl) {
    Assert(decl->getType() != nullptr, decl);
    m_ostream << header(decl) << std::endl;
    return true;
  }

  bool visitFunctionDecl(FunctionDecl *decl) {
    Assert(decl->getType() != nullptr, decl);
    m_ostream << header(decl) << cyan() << "'" << decl->getName() << "' "
              << blue() << decl->getRetType()->getName() << white()
              << std::endl;
    return true;
  }

  bool visitParamDecl(ParamDecl *decl) {
    Assert(decl->getType() != nullptr, decl);
    m_ostream << header(decl) << cyan() << "'" << decl->getName() << "' "
              << blue() << decl->getType()->getName() << white() << std::endl;
    return true;
  }

  bool visitVarDecl(VarDecl *decl) {
    Assert(decl->getType() != nullptr, decl);
    m_ostream << header(decl) << cyan() << "'" << decl->getName() << "' "
              << blue() << decl->getType()->getName() << white() << std::endl;
    return true;
  }

  bool visitArrayDecl(ArrayDecl *decl) {
    Assert(decl->getType() != nullptr, decl);
    Assert(decl->getElementType() != nullptr, decl);
    m_ostream << header(decl) << cyan() << "'" << decl->getName() << "' "
              << blue() << decl->getElementType()->getName() << white()
              << std::endl;
    return true;
  }

  bool visitDeclStmt(DeclStmt *stmt) {
    m_ostream << header(stmt) << std::endl;
    return true;
  }

  bool visitCompoundStmt(CompoundStmt *stmt) {
    m_ostream << header(stmt) << std::endl;
    return true;
  }
  bool visitIfStmt(IfStmt *stmt) {
    m_ostream << header(stmt) << std::endl;
    return true;
  }
  bool visitWhileStmt(WhileStmt *stmt) {
    m_ostream << header(stmt) << std::endl;
    return true;
  }
  bool visitContinueStmt(ContinueStmt *stmt) {
    m_ostream << header(stmt) << std::endl;
    return true;
  }
  bool visitBreakStmt(BreakStmt *stmt) {
    m_ostream << header(stmt) << std::endl;
    return true;
  }
  bool visitReturnStmt(ReturnStmt *stmt) {
    m_ostream << header(stmt) << std::endl;
    return true;
  }
  bool visitConstant(Constant *expr) {
    Assert(expr->getType() != nullptr, expr);
    m_ostream << header(expr) << "'" << expr->getValue() << "'" << std::endl;
    return true;
  }
  bool visitStringLiteral(StringLiteral *expr) {
    Assert(expr->getType() != nullptr, expr);
    m_ostream << header(expr) << "'" << expr->getValue() << "'" << std::endl;
    return true;
  }
  bool visitBinaryExpr(BinaryExpr *expr) {
    Assert(expr->getType() != nullptr, expr);
    m_ostream << header(expr) << "'" << getTokenName(expr->getOperator()) << "'"
              << std::endl;
    return true;
  }
  bool visitUnaryExpr(UnaryExpr *expr) {
    Assert(expr->getType() != nullptr, expr);
    m_ostream << header(expr) << "'" << getTokenName(expr->getOperator()) << "'"
              << std::endl;
    return true;
  }
  bool visitCallExpr(CallExpr *expr) {
    Assert(expr->getType() != nullptr, expr);
    m_ostream << header(expr) << std::endl;
    return true;
  }
  bool visitCastExpr(CastExpr *expr) {
    Assert(expr->getType() != nullptr, expr);
    m_ostream << header(expr) << blue() << expr->getToType()->getName()
              << white() << std::endl;
    return true;
  }
  bool visitDeclRefExpr(DeclRefExpr *expr) {
    Assert(expr->getType() != nullptr, expr);
    m_ostream << header(expr) << cyan() << "\'" << expr->getRefName() << "\' "
              << yellow() << ptrToString(expr->getRefDecl()) << white()
              << std::endl;
    return true;
  }
  bool visitArraySubscriptExpr(ArraySubscriptExpr *expr) {
    Assert(expr->getType() != nullptr, expr);
    m_ostream << header(expr) << std::endl;
    return true;
  }
};
} // namespace rvlang