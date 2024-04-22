#include "Sema.h"
#include "frontend/AstContext.h"
#include "frontend/Decl.h"
#include "frontend/Expr.h"
#include "frontend/Token.h"
#include "frontend/Type.h"
#include <llvm-14/llvm/Support/Casting.h>
#include <ranges>

namespace rvlang {
inline bool isSameType(const Type *l, const Type *r) {
  // AstContext holds all types
  return (l != nullptr) && (r != nullptr) && l == r;
}

Decl *Sema::getDeclByName(const std::string &name) {
  for (auto *scope : std::views::reverse(m_scopeChain)) {
    for (auto *decl : scope->getDecls()) {
      if (decl->getName() == name) {
        return decl;
      }
    }
  }
  return nullptr;
}

inline bool isBoolType(const Type *type) {
  return type->getKind() != Type::Kind::Void;
}

inline bool Sema::isValidCondition(Expr *cond) {
  return isBoolType(cond->getType());
}

bool checkType(const Type *type) {
  if (type == nullptr) {
    return false;
  }
  switch (type->getKind()) {
  case Type::Kind::Array:
  case Type::Kind::FloatPoint:
  case Type::Kind::Void:
  case Type::Kind::Integer:
    return true;
    break;
  case Type::Kind::Pointer:
    const auto *pt = llvm::dyn_cast<PointerType>(type);
    return pt != nullptr && checkType(pt->getPointeeType());
    break;
  }
  return false;
}

//------------- Traverser -------------
bool Sema::TraverseTranslationUnitDecl(TranslationUnitDecl *decl) {
  m_scopeChain.push_back(&decl->getScope());
  for (auto *d : decl->getDecls()) {
    if (!TraverseDecl(d)) {
      return false;
    }
  }
  if (!getDerived().visitTranslationUnitDecl(decl)) {
    return false;
  }
  m_scopeChain.pop_back();
  return true;
}

bool Sema::TraverseFunctionDecl(FunctionDecl *decl) {
  if (decl == nullptr) {
    return false;
  }
  m_scopeChain.back()->addDecl(decl);
  m_scopeChain.push_back(&decl->getScope());
  for (auto *param : decl->getParams()) {
    if (!getDerived().TraverseDecl(param)) {
      return false;
    }
  }
  m_retExprs.clear();
  auto *body = decl->getCompoundStmt();
  if (body != nullptr) {
    if (!getDerived().TraverseStmt(body)) {
      return false;
    }
  }
  // check ret type
  if (decl->getRetType()->getKind() != Type::Kind::Void) {
    for (Expr *expr : m_retExprs) {
      if (expr == nullptr || !isSameType(expr->getType(), decl->getRetType())) {
        SyntaxError(decl, "return type doesn't match");
      }
    }
  } else {
    if (!m_retExprs.empty()) {
      SyntaxError(decl, "return type doesn't match funtion decl");
    }
  }

  if (!getDerived().visitFunctionDecl(decl)) {
    return false;
  }

  m_scopeChain.pop_back();
  return true;
}

bool Sema::TraverseVarDecl(VarDecl *decl) {
  auto *initExpr = decl->getInitExpr();
  if (initExpr != nullptr) {
    if (!TraverseStmt(initExpr)) {
      return false;
    }
    Assert(initExpr->getType(), initExpr);
    Assert(decl->getType(), decl);

    if (!isSameType(initExpr->getType(), decl->getType())) {
      std::cout << "\n============ "
                << static_cast<int>(initExpr->getType()->getKind()) << "\n";

      std::cout << "\n============ "
                << static_cast<int>(decl->getType()->getKind()) << "\n";
      SyntaxError(decl, "type dismatch");
    }
  }
  if (!getDerived().visitVarDecl(decl)) {
    return false;
  }
  m_scopeChain.back()->addDecl(decl);
  return true;
}

bool Sema::TraverseParamDecl(ParamDecl *decl) {
  if (!getDerived().visitParamDecl(decl)) {
    return false;
  }
  m_scopeChain.back()->addDecl(decl);
  return true;
}

bool Sema::TraverseArrayDecl(ArrayDecl *decl) {
  if (!getDerived().visitArrayDecl(decl)) {
    return false;
  }
  m_scopeChain.back()->addDecl(decl);
  return true;
}

bool Sema::TraverseCompoundStmt(CompoundStmt *stmt) {
  m_scopeChain.push_back(&stmt->getScope());
  for (auto *s : stmt->getStmts()) {
    if (!TraverseStmt(s)) {
      return false;
    }
  }
  if (!getDerived().visitCompoundStmt(stmt)) {
    return false;
  }
  m_scopeChain.pop_back();
  return true;
}

//------------- visitor -------------
bool Sema::visitFunctionDecl(FunctionDecl *decl) {
  if (decl == nullptr) {
    return false;
  }
  return true;
}

bool Sema::visitIfStmt(IfStmt *stmt) {
  if (stmt == nullptr || stmt->getCond() == nullptr) {
    return false;
  }
  auto *cond = stmt->getCond();
  if (!isValidCondition(cond)) {
    SyntaxError(stmt, "if statement condition is not boolean");
  }
  return true;
}

bool Sema::visitWhileStmt(WhileStmt *stmt) {
  if (stmt == nullptr || stmt->getCond() == nullptr) {
    return false;
  }
  auto *cond = stmt->getCond();
  if (!isValidCondition(cond)) {
    SyntaxError(stmt, "while statement condition is not boolean");
  }
  return true;
}

bool Sema::visitDeclRefExpr(DeclRefExpr *expr) {
  if (expr == nullptr) {
    return false;
  }
  auto *decl = getDeclByName(expr->getRefName());
  if (decl == nullptr) {
    SyntaxError(expr, "identifier unkown: " + expr->getRefName());
  }
  expr->setRefDecl(decl);
  expr->setType(decl->getType());
  return true;
}

bool Sema::visitTranslationUnitDecl(TranslationUnitDecl *decl) {
  if (decl == nullptr) {
    return false;
  }
  auto *voidType = m_astCtx->newType<VoidType>();
  decl->setType(voidType);
  return true;
}
bool Sema::visitVarDecl(VarDecl *decl) {
  if (decl == nullptr) {
    return false;
  }
  Assert(checkType(decl->getType()), decl);
  return true;
}
bool Sema::visitParamDecl(ParamDecl *decl) {
  if (decl == nullptr) {
    return false;
  }
  Assert(checkType(decl->getType()), decl);
  return true;
}

bool Sema::visitArrayDecl(ArrayDecl *decl) {
  if (decl == nullptr) {
    return false;
  }
  Assert(checkType(decl->getType()), decl);
  return true;
}

bool Sema::visitCompoundStmt(CompoundStmt *stmt) {
  if (stmt == nullptr) {
    return false;
  }
  return true;
}
bool Sema::visitDeclStmt(DeclStmt *stmt) {
  if (stmt == nullptr) {
    return false;
  }
  return true;
}
bool Sema::visitContinueStmt(ContinueStmt *stmt) {
  if (stmt == nullptr) {
    return false;
  }
  return true;
}
bool Sema::visitBreakStmt(BreakStmt *stmt) {
  if (stmt == nullptr) {
    return false;
  }
  return true;
}

bool Sema::visitConstant(Constant *expr) { return true; }

bool Sema::visitStringLiteral(StringLiteral *expr) { return true; }

bool Sema::visitBinaryExpr(BinaryExpr *expr) {
  if (expr == nullptr) {
    return false;
  }
  auto *left = expr->getLeftOperand();
  auto *right = expr->getRightOperand();
  Assert(left != nullptr && checkType(left->getType()), expr);
  Assert(right != nullptr && checkType(right->getType()), expr);

  // Pointer op Integer
  // Integer op Integer
  //
  if (!isSameType(left->getType(), right->getType())) {
    SyntaxError(expr, "type dismatch");
  }

  const Type *leftType = left->getType();
  if (leftType == nullptr) {
    SyntaxError(expr, "operand type unkown");
  }
  const Type *type = nullptr;

  switch (expr->getOperator()) {
  case Token::PLUS:
  case Token::MINUS:
  case Token::SLASH:
  case Token::STAR:
  case Token::PERCENT:
  case Token::LSHIFT:
  case Token::RSHIFT:
    type = leftType;
    break;
  case Token::EQ:
  case Token::NEQ:
  case Token::GE:
  case Token::LE:
  case Token::GT:
  case Token::LT:
  case Token::LOGIC_AND:
  case Token::LOGIC_OR:
  case Token::AND:
  case Token::OR:
  case Token::XOR: {
    type = m_astCtx->getNamedType("char");
    if (type == nullptr) {
      type = m_astCtx->newType<IntegerType>("char", 1, false);
    }
  } break;
  case Token::ASSIGN: {
    const Type *rightType = right->getType();
    type = rightType;
  } break;
  default:
    SyntaxError(expr, "unkown operator");
    break;
  }
  expr->setType(type);
  return true;
}

bool Sema::visitUnaryExpr(UnaryExpr *expr) {
  if (expr == nullptr) {
    return false;
  }
  // if (expr->getOperand() != nullptr) {
  //   return true;
  // }
  const Type *operandType = expr->getOperand()->getType();
  if (operandType == nullptr) {
    SyntaxError(expr, "operand type unkown");
  }
  const Type *type = nullptr;
  switch (expr->getOperator()) {
  case Token::LOGIC_NOT:
    type = operandType;
    break;
  case Token::NOT:
    type = operandType;
    break;
  case Token::AND: {
    std::string name = "(" + operandType->getName() + ")*";
    type = m_astCtx->newType<rvlang::PointerType>(name, operandType);
  } break;
  case Token::STAR: {
    if (operandType->getKind() == Type::Kind::Pointer) {
      auto *pt = llvm::dyn_cast<PointerType>(operandType);
      Assert(pt != nullptr, expr);
      type = pt->getPointeeType();
    } else if (operandType->getKind() == Type::Kind::Array) {
      auto *at = llvm::dyn_cast<ArrayType>(operandType);
      Assert(at != nullptr, expr);
      type = at->getElementType();
    } else {
      SyntaxError(expr, "dereference expression invalid");
    }
  } break;
  default:
    break;
  }

  expr->setType(type);
  return true;
}

bool Sema::visitCallExpr(CallExpr *expr) {
  if (expr == nullptr) {
    return false;
  }
  expr->setType(expr->getDeclRefExpr()->getType());
  return true;
}
bool Sema::visitCastExpr(CastExpr *expr) {
  if (expr == nullptr) {
    return false;
  }
  return true;
}

bool Sema::visitArraySubscriptExpr(ArraySubscriptExpr *expr) {
  if (expr == nullptr) {
    return false;
  }

  auto *declRefExpr = llvm::dyn_cast<DeclRefExpr>(expr->getArrayDeclRef());
  Assert(declRefExpr, expr);

  auto *arrayDecl = llvm::dyn_cast<ArrayDecl>(declRefExpr->getRefDecl());
  Assert(arrayDecl, arrayDecl);

  expr->setType(arrayDecl->getElementType());

  return true;
}
} // namespace rvlang