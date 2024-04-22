#pragma once
#include "AstVisitor.h"
#include "Scope.h"
#include "frontend/Ast.h"
#include "frontend/AstContext.h"
#include "frontend/Expr.h"
#include <llvm-14/llvm/Support/Casting.h>

#include <vector>


namespace rvlang {

// check decl reference
// set type
// check type consistency
// check return stmt;
// set scope, global, local
// const
// linkage
// call parameters
// cast type
class Sema : public AstVisitor<Sema> {
private:
  AstContext *m_astCtx;

  std::vector<Scope *> m_scopeChain;

  std::vector<Expr *> m_retExprs;

public:
  Sema(AstContext *astCtx) : m_astCtx(astCtx) {
    m_traverseOrder = TraverseOrder::PostOrder;
  }
  ~Sema() {}

private:
  Decl *getDeclByName(const std::string &name);
  bool isValidCondition(Expr *cond);

public:
  // rewrite Traverse*, add scope
  bool TraverseTranslationUnitDecl(TranslationUnitDecl *decl);
  bool TraverseFunctionDecl(FunctionDecl *decl);
  bool TraverseVarDecl(VarDecl *decl);
  bool TraverseParamDecl(ParamDecl *decl);
  bool TraverseArrayDecl(ArrayDecl *decl);
  bool TraverseCompoundStmt(CompoundStmt *stmt);

public:
  bool visitFunctionDecl(FunctionDecl *decl);
  bool visitIfStmt(IfStmt *stmt);
  bool visitWhileStmt(WhileStmt *stmt);
  bool visitDeclRefExpr(DeclRefExpr *expr);
  bool visitArraySubscriptExpr(ArraySubscriptExpr *expr);
  bool visitReturnStmt(ReturnStmt *stmt) {
    if (stmt == nullptr) {
      return false;
    }
    m_retExprs.push_back(stmt->getReturnExpr());
    return true;
  }

  bool visitTranslationUnitDecl(TranslationUnitDecl *decl);
  bool visitVarDecl(VarDecl *decl);
  bool visitParamDecl(ParamDecl *decl);
  bool visitArrayDecl(ArrayDecl *decl);

  bool visitCompoundStmt(CompoundStmt *stmt);
  bool visitDeclStmt(DeclStmt *stmt);
  bool visitContinueStmt(ContinueStmt *stmt);
  bool visitBreakStmt(BreakStmt *stmt);

  bool visitConstant(Constant *expr);
  bool visitStringLiteral(StringLiteral *expr);
  bool visitBinaryExpr(BinaryExpr *expr);
  bool visitUnaryExpr(UnaryExpr *expr);
  bool visitCallExpr(CallExpr *expr);
  bool visitCastExpr(CastExpr *expr);
};
} // namespace rvlang