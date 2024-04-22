
#include "Driver.h"

namespace rvlang {
void Driver::compile(const std::string &file) {
  m_file = file;
  m_compiler.parse(file);

  m_compiler.doAnalysis();
  m_compiler.dumpAst();

  m_compiler.toIR();
}
} // namespace rvlang