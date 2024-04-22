#pragma once

#include <string>
#include <unordered_map>
#include <variant>

namespace rvlang {

class Decl;

struct Symbol {
  const std::string_view m_name;
  Decl *decl;
};

class SymbolTable {
private:
  std::unordered_map<std::string_view, Symbol> m_map;

public:
  SymbolTable() {}
  ~SymbolTable() {}

  Symbol *getSymbol(std::string_view name) {
    auto itor = m_map.find(name);
    return (itor == m_map.end()) ? nullptr : &(itor->second);
  }
  Decl *getDecl(std::string_view name) {
    auto itor = m_map.find(name);
    return (itor == m_map.end()) ? nullptr : itor->second.decl;
  }
};
} // namespace rvlang