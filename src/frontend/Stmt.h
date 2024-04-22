#pragma once

#include "Ast.h"
#include "Scope.h"

#include <vector>

namespace rvlang {
class DeclStmt : public Stmt {
private:
  Decl *m_decl;

public:
  DeclStmt(yy::location loc, Decl *decl)
      : Stmt(StmtKind::DeclStmt, loc), m_decl(decl) {}
  ~DeclStmt() {}

  Decl *getDecl() { return m_decl; }

  static bool classof(const Stmt *n) {
    return n->getKind() == StmtKind::DeclStmt;
  }
};

class CompoundStmt : public Stmt {
private:
  std::vector<Stmt *> m_stmts;
  Scope m_scope;

public:
  CompoundStmt(yy::location loc, std::vector<Stmt *> stmts = {})
      : Stmt(StmtKind::CompoundStmt, loc), m_stmts(std::move(stmts)) {}
  ~CompoundStmt() {}

  Scope &getScope() { return m_scope; }
  std::vector<Stmt *> &getStmts() { return m_stmts; }

  static bool classof(const Stmt *n) {
    return n->getKind() == StmtKind::CompoundStmt;
  }
};

class IfStmt : public Stmt {
private:
  Expr *m_condition;
  CompoundStmt *m_thenStmt;
  CompoundStmt *m_elseStmt;

public:
  IfStmt(yy::location loc, Expr *cond, CompoundStmt *thenStmt,
         CompoundStmt *elseStmt = nullptr)
      : Stmt(StmtKind::IfStmt, loc), m_condition(cond), m_thenStmt(thenStmt),
        m_elseStmt(elseStmt) {}
  ~IfStmt() {}

  Expr *getCond() { return m_condition; }

  CompoundStmt *getThenStmt() { return m_thenStmt; }
  CompoundStmt *getElseStmt() { return m_elseStmt; }

  static bool classof(const Stmt *n) {
    return n->getKind() == StmtKind::IfStmt;
  }
};

class WhileStmt : public Stmt {
private:
  Expr *m_condition;
  CompoundStmt *m_compoundStmt;

public:
  WhileStmt(yy::location loc, Expr *cond, CompoundStmt *compoundStmt)
      : Stmt(StmtKind::WhileStmt, loc), m_condition(cond),
        m_compoundStmt(compoundStmt) {}
  ~WhileStmt() {}

  Expr *getCond() { return m_condition; }

  CompoundStmt *getCompoundStmt() { return m_compoundStmt; }

  static bool classof(const Stmt *n) {
    return n->getKind() == StmtKind::WhileStmt;
  }
};

class ContinueStmt : public Stmt {
public:
  ContinueStmt(yy::location loc) : Stmt(StmtKind::ContinueStmt, loc) {}
  ~ContinueStmt() {}

  static bool classof(const Stmt *n) {
    return n->getKind() == StmtKind::ContinueStmt;
  }
};

class BreakStmt : public Stmt {
public:
  BreakStmt(yy::location loc) : Stmt(StmtKind::BreakStmt, loc) {}
  ~BreakStmt() {}

  static bool classof(const Stmt *n) {
    return n->getKind() == StmtKind::BreakStmt;
  }
};

class ReturnStmt : public Stmt {
private:
  Expr *m_retExpr;

public:
  ReturnStmt(yy::location loc, Expr *retExpr)
      : Stmt(StmtKind::ReturnStmt, loc), m_retExpr(retExpr) {}
  ~ReturnStmt() {}

  Expr *getReturnExpr() { return m_retExpr; }

  static bool classof(const Stmt *n) {
    return n->getKind() == StmtKind::ReturnStmt;
  }
};

}; // namespace rvlang