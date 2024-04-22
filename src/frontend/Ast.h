#pragma once

#include "Common.h"
#include "Type.h"
#include "frontend/parser/location.hh"
#include <string_view>

namespace rvlang {
class Decl {
public:
  enum class DeclKind {
    TranslationUnitDecl,
    FunctionDecl,
    ParamDecl,
    VarDecl,
    ArrayDecl,

    NUM_OF_KIND
  };

protected:
  const DeclKind m_kind;
  const Type *m_type;
  const yy::location m_loc;

public:
  Decl(DeclKind kind, const Type *t, const yy::location &loc)
      : m_kind(kind), m_type(t), m_loc(loc) {}
  virtual ~Decl() {}

  const Type *getType()const  { return m_type; }
  void setType(const Type *t) { m_type = t; }

  virtual const std::string &getName() const = 0;

  DeclKind getKind() const { return m_kind; }

  const std::string_view getKindName() const;

  const yy::location &getLocation() const { return m_loc; }
};

class Stmt {
public:
  enum class StmtKind {
    Constant,
    StringLiteral,

    BinaryExpr,
    UnaryExpr,
    CallExpr,
    CastExpr,
    DeclRefExpr,
    ArraySubscriptExpr,

    CompoundStmt,
    DeclStmt,
    IfStmt,
    WhileStmt,
    ContinueStmt,
    BreakStmt,
    ReturnStmt,

    NUM_OF_KIND
  };

private:
  const StmtKind m_kind;
  const yy::location m_loc;

public:
  Stmt(StmtKind kind, const yy::location &loc) : m_kind(kind), m_loc(loc) {}
  virtual ~Stmt() {}

  StmtKind getKind() const { return m_kind; }

  const std::string_view getKindName() const;
  const yy::location &getLocation() const { return m_loc; }
};

class Expr : public Stmt {
protected:
  const Type *m_type;

public:
  Expr(StmtKind kind, const Type *t, const yy::location &loc)
      : Stmt(kind, loc), m_type(t) {}
  virtual ~Expr() {}

  const Type *getType() const { return m_type; }
  void setType(const Type *type) { m_type = type; }
};

template <typename Node>
inline void
Assert(bool condition, Node *node, const std::string &msg = "",
       const std::source_location location = std::source_location::current())
  requires std::is_base_of<rvlang::Stmt, Node>::value
           || std::is_base_of<rvlang::Decl, Node>::value
{
  if (!condition) {
    const auto &loc = node->getLocation();
    ThrowRuntimeError(green() + *(loc.begin.filename) + ":" +
                          std::to_string(loc.begin.line) + ":" +
                          std::to_string(loc.begin.column) +
                          ": Assertion failed: " + msg,
                      location);
  }
}

template <typename Node>
inline void SyntaxError(
    Node *node, const std::string &msg,
    const std::source_location location = std::source_location::current())
  requires std::is_base_of<rvlang::Stmt, Node>::value
           || std::is_base_of<rvlang::Decl, Node>::value
{
  const auto &loc = node->getLocation();
  ThrowRuntimeError(green() + *(loc.begin.filename) + ":" +
                        std::to_string(loc.begin.line) + ": " + msg,
                    location);
}
} // namespace rvlang