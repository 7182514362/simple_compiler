#pragma once
#include "Ast.h"
#include "Token.h"
#include "Type.h"
#include <string>
#include <vector>

namespace rvlang {
class UnaryExpr : public Expr {
private:
  Token m_op;
  Expr *m_operand;

public:
  UnaryExpr(yy::location loc, Token op, Expr *operand, const Type *resultType)
      : Expr(StmtKind::UnaryExpr, resultType, loc), m_op(op),
        m_operand(operand) {}
  // UnaryExpr(Token op, Expr *operand)
  //     : UnaryExpr(op, operand, operand->getType()) {}
  ~UnaryExpr() {}

  Token getOperator() { return m_op; }
  Expr *getOperand() { return m_operand; }

  static bool classof(const Expr *n) {
    return n->getKind() == StmtKind::UnaryExpr;
  }
};

class BinaryExpr : public Expr {
private:
  Token m_op;
  Expr *m_lOperand;
  Expr *m_rOperand;

public:
  BinaryExpr(yy::location loc, Token op, Expr *left, Expr *right,
             const Type *resultType)
      : Expr(StmtKind::BinaryExpr, resultType, loc), m_op(op), m_lOperand(left),
        m_rOperand(right) {}
  // BinaryExpr(Token op, Expr *left, Expr *right)
  //     : BinaryExpr(op, left, right, left->getType()) {}

  ~BinaryExpr() {}

  Expr *getLeftOperand() { return m_lOperand; }
  Expr *getRightOperand() { return m_rOperand; }

  Token getOperator() { return m_op; }

  static bool classof(const Expr *n) {
    return n->getKind() == StmtKind::BinaryExpr;
  }
};

class Constant : public Expr {
private:
  int m_value;

public:
  Constant(yy::location loc, int v, const Type *type)
      : Expr(StmtKind::Constant, type, loc), m_value(v) {}
  ~Constant() {}

  int getValue() const { return m_value; }

  static bool classof(const Expr *n) {
    return n->getKind() == StmtKind::Constant;
  }
};

class StringLiteral : public Expr {
private:
  std::string m_value;

public:
  StringLiteral(yy::location loc, const std::string &v, const Type *type)
      : Expr(StmtKind::StringLiteral, type, loc), m_value(v) {}
  ~StringLiteral() {}

  int getLength() const { return m_value.length(); }

  const std::string &getValue() const { return m_value; }

  static bool classof(const Expr *n) {
    return n->getKind() == StmtKind::StringLiteral;
  }
};

class DeclRefExpr : public Expr {
private:
  const std::string m_refName;
  Decl *m_decl;

public:
  DeclRefExpr(yy::location loc, const std::string &refName, const Type *type)
      : Expr(StmtKind::DeclRefExpr, type, loc), m_refName(refName),
        m_decl(nullptr) {} // decl will be set by sema
  ~DeclRefExpr() {}

  const std::string &getRefName() { return m_refName; }

  Decl *getRefDecl() { return m_decl; }
  void setRefDecl(Decl *d) { m_decl = d; }

  static bool classof(const Expr *n) {
    return n->getKind() == StmtKind::DeclRefExpr;
  }
};

class CallExpr : public Expr {
private:
  DeclRefExpr *m_declRef;
  std::vector<Expr *> m_params;

public:
  CallExpr(yy::location loc, DeclRefExpr *declRef,
           std::vector<Expr *> params = {})
      : Expr(StmtKind::CallExpr, nullptr, loc), m_declRef(declRef),
        m_params(std::move(params)) {}
  ~CallExpr() {}

  DeclRefExpr *getDeclRefExpr() { return m_declRef; }

  std::vector<Expr *> &getParams() { return m_params; }

  static bool classof(const Expr *n) {
    return n->getKind() == StmtKind::CallExpr;
  }
};

class CastExpr : public Expr {
private:
  Expr *m_operand;
  const Type *m_toType;

public:
  CastExpr(yy::location loc, Expr *operand, const Type *fromType,
           const Type *toType)
      : Expr(StmtKind::CastExpr, fromType, loc), m_operand(operand),
        m_toType(toType) {}
  ~CastExpr() {}

  const Type *getToType() const { return m_toType; }

  Expr *getOperand() { return m_operand; }

  static bool classof(const Expr *n) {
    return n->getKind() == StmtKind::CastExpr;
  }
};

// todo: add to astvisitor sema dumper
// codegen
class ArraySubscriptExpr : public Expr {
private:
  Expr *m_arrayDeclRef;
  Expr *m_indexExpr;

public:
  ArraySubscriptExpr(yy::location loc, DeclRefExpr *declRef, Expr *index)
      : Expr(StmtKind::ArraySubscriptExpr, nullptr, loc),
        m_arrayDeclRef(declRef), m_indexExpr(index) {}
  ~ArraySubscriptExpr() {}

  Expr *getArrayDeclRef() { return m_arrayDeclRef; }

  Expr *getIndexExpr() { return m_indexExpr; }

  static bool classof(const Expr *n) {
    return n->getKind() == StmtKind::ArraySubscriptExpr;
  }
};

} // namespace rvlang