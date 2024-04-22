#pragma once

#include "frontend/CompilerInstance.h"

namespace rvlang {
class Driver {
private:
  std::string m_file;

  CompilerInstance m_compiler;

public:
  Driver() {}
  ~Driver() {}

  CompilerInstance &getCompiler() { return m_compiler; }

  void compile(const std::string &file);
};
} // namespace rvlang