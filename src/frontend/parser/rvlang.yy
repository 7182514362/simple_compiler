%skeleton "lalr1.cc" // -*- C++ -*-
%require "3.8.2"
%header

%define api.token.raw

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
#include <string>
#include <memory>

#include "frontend/Decl.h"
#include "frontend/Stmt.h"
#include "frontend/Expr.h"
#include "frontend/Token.h"
#include "frontend/Type.h"

namespace rvlang{
  class CompilerInstance;
}
}

// The parsing context.
%param { rvlang::CompilerInstance& compiler }

%locations

%define parse.trace
%define parse.error detailed
%define parse.lac full

%code {
#include "frontend/CompilerInstance.h"
}

%define api.token.prefix {TOK_}
%token <rvlang::Token>
  ASSIGN  "="
  MINUS   "-"
  PLUS    "+"
  STAR    "*"
  SLASH   "/"
  LPAREN  "("
  RPAREN  ")"
  LBRACE  "{"
  RBRACE  "}"
  
  LBRACKET  "["
  RBRACKET  "]"

  EQ      "=="
  NEQ     "!="
  GT      ">"
  LT      "<"
  GE      ">="
  LE      "<="
  LOGIC_AND   "&&"
  LOGIC_OR    "||"
  LOGIC_NOT   "!"

  PERCENT "%"
  LSHIFT  "<<"
  RSHIFT  ">>"

  NOT     "~"
  AND     "&"
  OR      "|"
  XOR     "^"

  VOID    "void"
  CHAR    "char"
  SHORT   "short"
  INT     "int"

  SIGNED  "signed"
  UNSIGNED  "unsigned"

  FLOAT   "float"

  IF      "if"
  ELSE    "else"
  FOR     "for"
  WHILE   "while"

  SEMICOLON   ";"
  COMMA       ","
  CONTINUE    "continue"
  BREAK       "break"
  RETURN      "return"
  STRUCT    "struct"
;

%token <std::string> IDENTIFIER STRING_LITERAL
;
%token <int> CONSTANT
;

%nterm <rvlang::Token> binary_operator
;

%nterm <std::vector<int>> elements
;

%nterm <std::vector<rvlang::Decl*>> declaration_list
;

%nterm <std::vector<rvlang::ParamDecl*>> parameter_decl_list
;

%nterm <std::vector<rvlang::Stmt*>> statement_list
;

%nterm <std::vector<rvlang::Expr*>> parameter_list
;

%nterm <rvlang::Decl*> translation_unit declaration
  variable_declaration function_declaration array_declaration
;

%nterm <rvlang::ParamDecl*> parameter_declaration
;

%nterm <rvlang::Stmt*>
  declare_statement statement
  declaration_or_statement
  expression_statement
  selection_statement
  iteration_statement jump_statement
;

%nterm <rvlang::CompoundStmt*> compound_statement
;

%nterm <rvlang::Expr*>
  parameter expression unary_expression binary_expression
  assignment_expression call_expression dereference_expression
  array_subscript_expression
;

%nterm <rvlang::DeclRefExpr*> declaration_ref_expression
;


%nterm <const rvlang::Type*>
  type_specifier delaration_specifiers pointer
;

%%
%start translation_unit;
translation_unit
  : declaration_list {
      auto* unit = compiler.getTranslationUnit();
      for(auto* d: $1) {
        unit->addDecl(d);
      }
    }
;

declaration_list: declaration {
      $$ = std::vector<rvlang::Decl*>();
      $$.push_back($1);
    } 
  | declaration_list declaration {
      $1.push_back($2);
      $$ = std::move($1);
    }
;

declaration: function_declaration { $$ = $1; }
  | variable_declaration { $$ = $1; }
  | array_declaration { $$ = $1; }
;

function_declaration
  : delaration_specifiers IDENTIFIER "(" parameter_decl_list ")" ";" {
      $$ = compiler.getAstContext()->newNode<rvlang::FunctionDecl>(compiler.location(), $1, $2, std::move($4));
    }
  | delaration_specifiers IDENTIFIER "(" parameter_decl_list ")" compound_statement {
      $$ = compiler.getAstContext()->newNode<rvlang::FunctionDecl>(compiler.location(), $1, $2, std::move($4), $6);
    }
;

array_declaration
  : delaration_specifiers IDENTIFIER "[" CONSTANT "]" ";" {
      std::string arrayTypeName = "(" + $1->getName() + ")*";
      auto* t = compiler.getAstContext()->getNamedType(arrayTypeName);
      if (t == nullptr) {
        t = compiler.getAstContext()->newType<rvlang::PointerType>(arrayTypeName, $1);
      }
      $$ = compiler.getAstContext()->newNode<rvlang::ArrayDecl>(compiler.location(), $2, t, $1, $4);
    }
  | delaration_specifiers IDENTIFIER "[" CONSTANT "]" "=" "{" elements "}" ";" {
      if ($4 != $8.size()) {
        throw yy::parser::syntax_error(compiler.location(), "array size doesn't match");
      }
      std::string arrayTypeName = "(" + $1->getName() + ")*";
      auto* t = compiler.getAstContext()->getNamedType(arrayTypeName);
      if (t == nullptr) {
        t = compiler.getAstContext()->newType<rvlang::PointerType>(arrayTypeName, $1);
      }
      $$ = compiler.getAstContext()->newNode<rvlang::ArrayDecl>(compiler.location(), $2, t, $1, $4, $8);
    }
;

elements
  : CONSTANT {
      $$ = std::vector<int>();
      $$.push_back($1);
    }
  | elements "," CONSTANT {
      $1.push_back($3);
      $$ = std::move($1);
    }
;


delaration_specifiers
  : type_specifier { $$ = $1; }
  | pointer { $$ = $1; }
;

pointer
  : type_specifier "*" {
      std::string typeName = "(" + $1->getName() + ")*";
      auto* t = compiler.getAstContext()->getNamedType(typeName);
      if (t == nullptr) {
        t = compiler.getAstContext()->newType<rvlang::PointerType>(typeName, $1);
      }
      $$ = t;
    }
  | pointer "*" {
      std::string typeName = "(" + $1->getName() + ")*";
      auto* t = compiler.getAstContext()->getNamedType(typeName);
      if (t == nullptr) {
        t = compiler.getAstContext()->newType<rvlang::PointerType>(typeName, $1);
      }
      $$ = t;
    }
;

type_specifier
  : "void" {
      $$ = compiler.getAstContext()->newType<rvlang::VoidType>();
    }
  | "char" {
      $$ = compiler.getAstContext()->newType<rvlang::IntegerType>("char", 1, true);
    }
  | "short" {
      $$ = compiler.getAstContext()->newType<rvlang::IntegerType>("short", 2, true);
    }
  | "int" {
      $$ = compiler.getAstContext()->newType<rvlang::IntegerType>("int", 4, true);
    }
  | "long" {
      $$ = compiler.getAstContext()->newType<rvlang::IntegerType>("long", 8, true);
    }
  | "float" {
      $$ = compiler.getAstContext()->newType<rvlang::FloatPointType>();
    }
  | "unsigned" "char" {
      $$ = compiler.getAstContext()->newType<rvlang::IntegerType>("char", 1, false);
    }
  | "unsigned" "short" {
      $$ = compiler.getAstContext()->newType<rvlang::IntegerType>("short", 2, false);
    }
  | "unsigned" "int" {
      $$ = compiler.getAstContext()->newType<rvlang::IntegerType>("int", 4, false);
    }
  | "unsigned" "long" {
      $$ = compiler.getAstContext()->newType<rvlang::IntegerType>("long", 8, false);
    }
;

parameter_decl_list
  : { $$ = std::vector<rvlang::ParamDecl*>(); }
  | parameter_declaration { 
      $$ = std::vector<rvlang::ParamDecl*>();
      $$.push_back($1);
    }
  | parameter_decl_list "," parameter_declaration {
      $1.push_back($3);
      $$ = std::move($1);
    }
;

parameter_declaration
  : delaration_specifiers IDENTIFIER {
      $$ = compiler.getAstContext()->newNode<rvlang::ParamDecl>(compiler.location(), $1, $2);
    }
;

compound_statement
  : "{" statement_list "}" {
      $$ = compiler.getAstContext()->newNode<rvlang::CompoundStmt>(compiler.location(), std::move($2));
    }
  | "{" "}" { $$ = compiler.getAstContext()->newNode<rvlang::CompoundStmt>(compiler.location()); }
;

statement_list
  : declaration_or_statement {
      $$ = std::vector<rvlang::Stmt*>();
      $$.push_back($1);
    }
  | statement_list declaration_or_statement {
      $1.push_back($2);
      $$ = std::move($1);
    }
;

declaration_or_statement
  : statement   { $$ = $1; }
  | declare_statement { $$ = $1; }
;

declare_statement: variable_declaration { $$ = compiler.getAstContext()->newNode<rvlang::DeclStmt>(compiler.location(), $1); }
;

variable_declaration
  : delaration_specifiers IDENTIFIER ";" {
      $$ = compiler.getAstContext()->newNode<rvlang::VarDecl>(compiler.location(), $1, $2);
    }
  | delaration_specifiers IDENTIFIER "=" expression ";" {
      $$ = compiler.getAstContext()->newNode<rvlang::VarDecl>(compiler.location(), $1, $2, $4);
    }
;

expression
  : CONSTANT {
      auto* intType = compiler.getAstContext()->getNamedType("int");
      if (intType == nullptr) {
        intType = compiler.getAstContext()->newType<rvlang::IntegerType>("int", 4, true);
      }
      $$ = compiler.getAstContext()->newNode<rvlang::Constant>(compiler.location(), $1, intType); 
    }
  | STRING_LITERAL {
      auto* charType = compiler.getAstContext()->getNamedType("char");
      if(charType == nullptr) {
        charType = compiler.getAstContext()->newType<rvlang::IntegerType>("char", 1, true);
      }
      auto* stringType = compiler.getAstContext()->getNamedType("(char)*");
      if (stringType == nullptr) {
        stringType = compiler.getAstContext()->newType<rvlang::PointerType>("(char)*", charType);
      }
      $$ = compiler.getAstContext()->newNode<rvlang::StringLiteral>(compiler.location(), $1, nullptr);
    }
  | declaration_ref_expression { $$ = $1; }
  | unary_expression  { $$ = $1; }
  | binary_expression { $$ = $1; }
  | call_expression   { $$ = $1; }
  | "(" expression ")"  { $$ = $2; }
  | "(" delaration_specifiers ")" expression {
      $$ = compiler.getAstContext()->newNode<rvlang::CastExpr>(compiler.location(), $4, nullptr, $2);
    }
  | array_subscript_expression { $$ = $1; }
;

declaration_ref_expression
  : IDENTIFIER {
      $$ = compiler.getAstContext()->newNode<rvlang::DeclRefExpr>(compiler.location(), $1, nullptr);
    }
;

array_subscript_expression
  : declaration_ref_expression "[" expression "]" {
      $$ = compiler.getAstContext()->newNode<rvlang::ArraySubscriptExpr>(compiler.location(), $1, $3);
    }
;

unary_expression
  : "!" expression {
      $$ = compiler.getAstContext()->newNode<rvlang::UnaryExpr>(compiler.location(), $1, $2, nullptr);
    }
  | "~" expression  { $$ = compiler.getAstContext()->newNode<rvlang::UnaryExpr>(compiler.location(), $1, $2, nullptr); }
  | "&" expression  {
      $$ = compiler.getAstContext()->newNode<rvlang::UnaryExpr>(compiler.location(), $1, $2, nullptr);
    }
  | dereference_expression { $$ = $1; }
;

dereference_expression
  : "*" expression  { $$ = compiler.getAstContext()->newNode<rvlang::UnaryExpr>(compiler.location(), $1, $2, nullptr); }
;

binary_expression
  : expression binary_operator expression {
      $$ = compiler.getAstContext()->newNode<rvlang::BinaryExpr>(compiler.location(), $2, $1, $3, nullptr);
    }
;

binary_operator
  : "+" { $$ = $1; }
  | "-" { $$ = $1; }
  | "*" { $$ = $1; }
  | "/" { $$ = $1; }
  | "%" { $$ = $1; }
  | "<<" { $$ = $1; }
  | ">>" { $$ = $1; }
  | "==" { $$ = $1; }
  | "!=" { $$ = $1; }
  | ">=" { $$ = $1; }
  | "<=" { $$ = $1; }
  | ">" { $$ = $1; }
  | "<" { $$ = $1; }
  | "&&" { $$ = $1; }
  | "||" { $$ = $1; }
  | "&" { $$ = $1; }
  | "|" { $$ = $1; }
  | "^" { $$ = $1; }
;

statement
  : expression_statement { $$ = $1; }
  | selection_statement { $$ = $1; }
  | iteration_statement { $$ = $1; }
  | jump_statement  { $$ = $1; }
;

expression_statement: assignment_expression { $$ = $1; }
  | call_expression ";" { $$ = $1; }
;

assignment_expression
  : dereference_expression "=" expression ";" {
      //auto* declRef = compiler.getAstContext()->newNode<rvlang::DeclRefExpr>(compiler.location(), $1, nullptr);
      $$ = compiler.getAstContext()->newNode<rvlang::BinaryExpr>(compiler.location(), $2, $1, $3, nullptr);
    }

  | declaration_ref_expression "=" expression ";" {
      //auto* declRef = compiler.getAstContext()->newNode<rvlang::DeclRefExpr>(compiler.location(), $1, nullptr);
      $$ = compiler.getAstContext()->newNode<rvlang::BinaryExpr>(compiler.location(), $2, $1, $3, nullptr);
    }

/*  
    | expression "=" call_expression ";" {
      //auto* declRef = compiler.getAstContext()->newNode<rvlang::DeclRefExpr>(compiler.location(), $1, nullptr);
      $$ = compiler.getAstContext()->newNode<rvlang::BinaryExpr>(compiler.location(), $2, $1, $3, nullptr);
    }
*/
;

call_expression
  : declaration_ref_expression "(" parameter_list ")" {
      // auto* declRef = compiler.getAstContext()->newNode<rvlang::DeclRefExpr>(compiler.location(), $1, nullptr);
      $$ = compiler.getAstContext()->newNode<rvlang::CallExpr>(compiler.location(), $1, std::move($3));
    }
  | declaration_ref_expression "(" ")" {
      // auto* declRef = compiler.getAstContext()->newNode<rvlang::DeclRefExpr>(compiler.location(), $1, nullptr);
      $$ = compiler.getAstContext()->newNode<rvlang::CallExpr>(compiler.location(), $1);
    }
;

parameter_list
  : parameter {
      $$ = std::vector<rvlang::Expr*>();
      $$.push_back($1);
    }
  | parameter_list "," parameter {
      $1.push_back($3);
      $$ = std::move($1);
    }
;

parameter: expression { $$ = $1; }
;

selection_statement
  : "if" "(" expression ")" compound_statement {
      $$ = compiler.getAstContext()->newNode<rvlang::IfStmt>(compiler.location(), $3, $5);
    }
  | "if" "(" expression ")" compound_statement "else" compound_statement {
      $$ = compiler.getAstContext()->newNode<rvlang::IfStmt>(compiler.location(), $3, $5, $7);
    }
;

iteration_statement
  : "while" "(" expression ")" compound_statement {
      $$ = compiler.getAstContext()->newNode<rvlang::WhileStmt>(compiler.location(), $3, $5);
    }
//  | "for" "(" expression ";" expression ";" expression ")" compound_statement
;

jump_statement
  : "continue" ";" {
      $$ = compiler.getAstContext()->newNode<rvlang::ContinueStmt>(compiler.location());
    }
  | "break" ";" {
      $$ = compiler.getAstContext()->newNode<rvlang::BreakStmt>(compiler.location());
    }
  | "return" expression ";" {
      $$ = compiler.getAstContext()->newNode<rvlang::ReturnStmt>(compiler.location(), $2);
    }
;

%left "&&" "||" "&" "|" "~" "^" "!"
;
%left "+" "-"
;
%left "*" "/"
;
%nonassoc "%" "<" ">" "=" "!=" "<=" ">=" "<<" ">>" "=="
;
%right "("
;
%left ")"
;

%%

void yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}