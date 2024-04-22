#pragma once

#include <vector>

namespace rvlang {
class Decl;
class Scope {
private:
  // decls within this scope
  std::vector<Decl *> m_decls;

public:
  Scope() = default;
  ~Scope() = default;

  const std::vector<Decl *> getDecls() const { return m_decls; }

  void addDecl(Decl *decl) { m_decls.push_back(decl); }
};
} // namespace rvlang