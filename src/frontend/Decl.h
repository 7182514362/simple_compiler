#pragma once

#include "Ast.h"
#include "Scope.h"
#include "Stmt.h"
#include "Type.h"
#include "frontend/parser/location.hh"
#include <string>
namespace rvlang {

class Expr;

class TranslationUnitDecl : public Decl {
private:
  const std::string m_name;
  std::vector<Decl *> m_decls;
  Scope m_scope;

public:
  TranslationUnitDecl(const std::string &name)
      : Decl(DeclKind::TranslationUnitDecl, nullptr, yy::location()),
        m_name(name) {}
  ~TranslationUnitDecl() = default;

  const std::string &getName() const { return m_name; }

  void addDecl(Decl *decl) {
    m_decls.push_back(decl);
    m_scope.addDecl(decl);
  }
  std::vector<Decl *> &getDecls() { return m_decls; }

  Scope &getScope() { return m_scope; }

  static bool classof(const Decl *n) {
    return n->getKind() == DeclKind::TranslationUnitDecl;
  }
};

class VarDecl : public Decl {
private:
  const std::string m_name;
  Expr *m_initExpr;

public:
  VarDecl(yy::location loc, const Type *type, const std::string &name,
          Expr *init = nullptr)
      : Decl(DeclKind::VarDecl, type, loc), m_name(name), m_initExpr(init) {}
  ~VarDecl() = default;

  const std::string &getName() const { return m_name; }

  Expr *getInitExpr() { return m_initExpr; }

  static bool classof(const Decl *n) {
    return n->getKind() == DeclKind::VarDecl;
  }
};

class ParamDecl : public Decl {
private:
  const std::string m_name;

public:
  ParamDecl(yy::location loc, const Type *type, const std::string &name)
      : Decl(DeclKind::ParamDecl, type, loc), m_name(name) {}
  ~ParamDecl() = default;

  const std::string &getName() const { return m_name; }

  static bool classof(const Decl *n) {
    return n->getKind() == DeclKind::ParamDecl;
  }
};

class FunctionDecl : public Decl {
private:
  const std::string m_name;
  std::vector<ParamDecl *> m_params;
  CompoundStmt *m_compoundStmt;
  Scope m_scope;

public:
  FunctionDecl(yy::location loc, const Type *retType, const std::string &name,
               std::vector<ParamDecl *> params,
               CompoundStmt *compoundStmt = nullptr)
      : Decl(DeclKind::FunctionDecl, retType, loc), m_name(name),
        m_params(std::move(params)), m_compoundStmt(compoundStmt) {}

  const Type *getRetType() const { return m_type; }

  void addParam(ParamDecl *param) { m_params.push_back(param); }
  const std::vector<ParamDecl *> &getParams() const { return m_params; }
  const std::string &getName() const { return m_name; }

  Scope &getScope() { return m_scope; }

  CompoundStmt *getCompoundStmt() { return m_compoundStmt; }

  static bool classof(const Decl *n) {
    return n->getKind() == DeclKind::FunctionDecl;
  }
};

class ArrayDecl : public Decl {
private:
  int m_length;
  const std::string m_name;
  const Type *m_elementType;
  std::vector<int> m_elements;

public:
  ArrayDecl(yy::location loc, const std::string &name, const Type *type,
            const Type *elementType, int length, std::vector<int> elements = {})
      : Decl(DeclKind::ArrayDecl, type, loc), m_length(length), m_name(name),
        m_elementType(elementType), m_elements(elements) {}
  ~ArrayDecl() = default;

  const std::string &getName() const { return m_name; }
  const Type *getElementType() const { return m_elementType; }

  int getLength() const { return m_length; }

  std::vector<int> &getElements() { return m_elements; }

  static bool classof(const Decl *n) {
    return n->getKind() == DeclKind::ArrayDecl;
  }
};

} // namespace rvlang