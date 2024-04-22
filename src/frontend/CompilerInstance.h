#pragma once

#include "Decl.h"

#include "frontend/AstContext.h"
#include "parser/Parser.h"
#include "parser/location.hh"

#define YY_DECL                                                                \
  yy::parser::symbol_type yylex(rvlang::CompilerInstance &compiler)
// ... and declare it for the parser's sake.
YY_DECL;

namespace rvlang {
class CompilerInstance {
private:
  std::string m_file;
  yy::location m_location;

  AstContext *m_astCtx;

public:
  CompilerInstance() : m_astCtx(&AstContext::getInstance()) {}
  ~CompilerInstance() {}

  yy::location &location() { return m_location; }

  void parse(const std::string &file);

  AstContext *getAstContext() { return m_astCtx; }

  TranslationUnitDecl *getTranslationUnit() {
    return m_astCtx->getTranslationUnit();
  }

  void dumpAst();
  void doAnalysis();
  void toIR();

private:
  void scanBegin();
  void scanEnd();
};

} // namespace rvlang