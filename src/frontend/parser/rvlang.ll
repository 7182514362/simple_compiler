%{ /* -*- C++ -*- */
# include <cerrno>
//# include <climits>
//# include <cstdlib>
#include <cstring> // strerror
#include <string>
#include "frontend/CompilerInstance.h"
#include "Parser.h"
%}

%option noyywrap nounput noinput batch debug

%{
  
%}

identifier    [_a-zA-Z][a-zA-Z_0-9]*
int   [-]?[0-9]+
hex   [0][xX][a-f0-9]
blank [ \t\r]
string_literal \".*\"

%{
// Code run each time a pattern is matched.
# define YY_USER_ACTION  loc.columns (yyleng);
%}
%%
%{
  // A handy shortcut to the location held by the driver.
  yy::location& loc = compiler.location();
  // Code run each time yylex is called.
  loc.step ();
%}
{blank}+   loc.step ();
\n+        loc.lines(yyleng); loc.step();

"-"   return yy::parser::make_MINUS(rvlang::Token::MINUS, loc);
"+"   return yy::parser::make_PLUS(rvlang::Token::PLUS, loc);
"*"   return yy::parser::make_STAR(rvlang::Token::STAR, loc);
"/"   return yy::parser::make_SLASH(rvlang::Token::SLASH, loc);
"("   return yy::parser::make_LPAREN(rvlang::Token::LPAREN, loc);
")"   return yy::parser::make_RPAREN(rvlang::Token::RPAREN, loc);
"="   return yy::parser::make_ASSIGN(rvlang::Token::ASSIGN, loc);
"}"   return yy::parser::make_RBRACE(rvlang::Token::RBRACE, loc);
"{"   return yy::parser::make_LBRACE(rvlang::Token::LBRACE, loc);
"]"   return yy::parser::make_RBRACKET(rvlang::Token::RBRACKET, loc);
"["   return yy::parser::make_LBRACKET(rvlang::Token::LBRACKET, loc);

","   return yy::parser::make_COMMA(rvlang::Token::COMMA, loc);
";"   return yy::parser::make_SEMICOLON(rvlang::Token::SEMICOLON, loc);

"<<"   return yy::parser::make_LSHIFT(rvlang::Token::LSHIFT, loc);
">>"   return yy::parser::make_RSHIFT(rvlang::Token::RSHIFT, loc);
">="   return yy::parser::make_GE(rvlang::Token::GE, loc);
"<="   return yy::parser::make_LE(rvlang::Token::LE, loc);
"!="   return yy::parser::make_NEQ(rvlang::Token::NEQ, loc);
"=="   return yy::parser::make_EQ(rvlang::Token::EQ, loc);
">"   return yy::parser::make_GT(rvlang::Token::GT, loc);
"<"   return yy::parser::make_LT(rvlang::Token::LT, loc);


"&&"  return yy::parser::make_LOGIC_AND(rvlang::Token::LOGIC_AND, loc);
"||"  return yy::parser::make_LOGIC_OR(rvlang::Token::LOGIC_OR, loc);
"!"  return yy::parser::make_LOGIC_NOT(rvlang::Token::LOGIC_NOT, loc);
"&"  return yy::parser::make_AND(rvlang::Token::AND, loc);
"|"  return yy::parser::make_OR(rvlang::Token::OR, loc);
"~"  return yy::parser::make_NOT(rvlang::Token::NOT, loc);
"^"  return yy::parser::make_XOR(rvlang::Token::XOR, loc);

"void"  return yy::parser::make_VOID(rvlang::Token::VOID, loc);
"char"  return yy::parser::make_CHAR(rvlang::Token::CHAR, loc);
"short"  return yy::parser::make_SHORT(rvlang::Token::SHORT, loc);
"int"  return yy::parser::make_INT(rvlang::Token::INT, loc);

"if"    return yy::parser::make_IF(rvlang::Token::IF, loc);
"else"  return yy::parser::make_ELSE(rvlang::Token::ELSE, loc);
"while"  return yy::parser::make_WHILE(rvlang::Token::WHILE, loc);
"continue"  return yy::parser::make_CONTINUE(rvlang::Token::CONTINUE, loc);
"break"  return yy::parser::make_BREAK(rvlang::Token::BREAK, loc);
"return"  return yy::parser::make_RETURN(rvlang::Token::RETURN, loc);
"signed"  return yy::parser::make_SIGNED(rvlang::Token::SIGNED, loc);
"unsigned"  return yy::parser::make_UNSIGNED(rvlang::Token::UNSIGNED, loc);

{int}   { int v = std::strtol(yytext, nullptr, 10); return yy::parser::make_CONSTANT(v, loc); }

{string_literal} { return yy::parser::make_STRING_LITERAL(yytext, loc); }

{identifier}    return yy::parser::make_IDENTIFIER(yytext, loc);
.         { throw yy::parser::syntax_error(loc, "invalid character: " + std::string(yytext)); }
<<EOF>>   return yy::parser::make_YYEOF(loc);
%%

namespace rvlang {
void CompilerInstance::scanBegin ()
{
  if (m_file.empty () || m_file == "-") {
    yyin = stdin;
  } else if (!(yyin = fopen (m_file.c_str (), "r"))) {
    std::cerr << "cannot open " << m_file << ": " << strerror (errno) << '\n';
    exit (EXIT_FAILURE);
  }
}

void CompilerInstance::scanEnd ()
{
  fclose (yyin);
}
}
