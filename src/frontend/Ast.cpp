#include "Ast.h"
#include <array>

namespace rvlang {
const std::string_view Decl::getKindName() const {
  static std::array<std::string_view, static_cast<int>(DeclKind::NUM_OF_KIND)>
      list = {"TranslationUnitDecl", "FunctionDecl", "ParamDecl", "VarDecl",
              "ArrayDecl"};
  return list[static_cast<int>(m_kind)];
}

const std::string_view Stmt::getKindName() const {
  static std::array<std::string_view, static_cast<int>(StmtKind::NUM_OF_KIND)>
      list = {
          "Constant",     "StringLiteral", "BinaryExpr",  "UnaryExpr",
          "CallExpr",     "CastExpr",      "DeclRefExpr", "ArraySubscriptExpr",
          "CompoundStmt", "DeclStmt",      "IfStmt",      "WhileStmt",
          "ContinueStmt", "BreakStmt",     "ReturnStmt"};
  return list[static_cast<int>(m_kind)];
}
} // namespace rvlang