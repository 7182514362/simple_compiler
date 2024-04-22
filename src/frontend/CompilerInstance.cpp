#include "CompilerInstance.h"

#include "frontend/AstDumper.h"
#include "frontend/IREmiter.h"
#include "frontend/Sema.h"

namespace rvlang {
void CompilerInstance::parse(const std::string &file) {
  m_file = file;
  m_location.initialize(&file);
  scanBegin();
  yy::parser parser(*this);
  parser.set_debug_level(1);
  parser();
  scanEnd();
}

void CompilerInstance::dumpAst() {
  AstDumper dumper;
  if (!dumper.TraverseDecl(getTranslationUnit())) {
    throw std::runtime_error("dump failed");
  }
}

void CompilerInstance::doAnalysis() {
  Sema sema(m_astCtx);
  if (!sema.TraverseDecl(getTranslationUnit())) {
    throw std::runtime_error("sema failed");
  }
}

void CompilerInstance::toIR() {
  IREmiter emiter;
  emiter.EmitDecl(getTranslationUnit());
}

} // namespace rvlang