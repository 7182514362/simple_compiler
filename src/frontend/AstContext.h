#pragma once

#include "Common.h"
#include "Decl.h"
#include "Type.h"
#include <map>
#include <memory>
#include <unordered_map>

#include <variant>

#include <type_traits>
#include <vector>

namespace rvlang {

template <typename T>
concept AstNodeConcreteType =
    std::is_base_of<Decl, T>::value || std::is_base_of<Stmt, T>::value;

class AstContext {
private:
  // all ast nodes
  std::vector<std::variant<UPtr<Decl>, UPtr<Stmt>>> m_nodes;
  // identifier table
  std::unordered_map<std::string_view, Decl *> m_identifiers;
  // holds all type
  std::map<std::string, UPtr<Type>> m_namedTypes;
  // source manager
  // translation unit
  UPtr<TranslationUnitDecl> m_translationUnit;
  // scope chain, current scope

public:
  static AstContext &getInstance() {
    static AstContext context;
    return context;
  }

private:
  AstContext()
      : m_translationUnit(
            std::make_unique<TranslationUnitDecl>("TranslationUnit")) {}

public:
  ~AstContext() {}

  TranslationUnitDecl *getTranslationUnit() { return m_translationUnit.get(); }

  const Type *getNamedType(const std::string &name) {
    auto itor = m_namedTypes.find(name);
    return (itor != m_namedTypes.end()) ? itor->second.get() : nullptr;
  }

  const Type *insertNamedType(const std::string &name, UPtr<Type> type) {
    auto itor = m_namedTypes.find(name);
    if (itor != m_namedTypes.end()) {
      return itor->second.get();
    }
    Type *p = type.get();
    m_namedTypes.insert({name, std::move(type)});
    return p;
  }

  template <AstNodeConcreteType Node, typename... Args>
  Node *newNode(Args... args) {
    auto node = std::make_unique<Node>(args...);
    auto *ptr = node.get();
    if constexpr (std::is_base_of<Decl, Node>::value) {
      auto *d = static_cast<Decl *>(ptr);
      m_identifiers.insert({d->getName(), d});
    }
    m_nodes.push_back(std::move(node));
    return ptr;
  }

  template <typename SubType, typename... Args>
  const Type *newType(Args... args)
    requires std::is_base_of<Type, SubType>::value
  {
    auto t = std::make_unique<SubType>(args...);
    const auto *ptr = getNamedType(t->getName());
    if (ptr != nullptr) {
      return ptr;
    }
    ptr = t.get();
    m_namedTypes.insert({ptr->getName(), std::move(t)});
    return ptr;
  }
};
} // namespace rvlang