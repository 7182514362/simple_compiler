// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "Parser.h"


// Unqualified %code blocks.
#line 35 "rvlang.yy"

#include "frontend/CompilerInstance.h"

#line 50 "Parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 142 "Parser.cpp"

  /// Build a parser object.
  parser::parser (rvlang::CompilerInstance& compiler_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      yy_lac_established_ (false),
      compiler (compiler_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_delaration_specifiers: // delaration_specifiers
      case symbol_kind::S_pointer: // pointer
      case symbol_kind::S_type_specifier: // type_specifier
        value.YY_MOVE_OR_COPY< const rvlang::Type* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CONSTANT: // CONSTANT
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_compound_statement: // compound_statement
        value.YY_MOVE_OR_COPY< rvlang::CompoundStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_declaration: // declaration
      case symbol_kind::S_function_declaration: // function_declaration
      case symbol_kind::S_array_declaration: // array_declaration
      case symbol_kind::S_variable_declaration: // variable_declaration
        value.YY_MOVE_OR_COPY< rvlang::Decl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration_ref_expression: // declaration_ref_expression
        value.YY_MOVE_OR_COPY< rvlang::DeclRefExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_array_subscript_expression: // array_subscript_expression
      case symbol_kind::S_unary_expression: // unary_expression
      case symbol_kind::S_dereference_expression: // dereference_expression
      case symbol_kind::S_binary_expression: // binary_expression
      case symbol_kind::S_assignment_expression: // assignment_expression
      case symbol_kind::S_call_expression: // call_expression
      case symbol_kind::S_parameter: // parameter
        value.YY_MOVE_OR_COPY< rvlang::Expr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameter_declaration: // parameter_declaration
        value.YY_MOVE_OR_COPY< rvlang::ParamDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration_or_statement: // declaration_or_statement
      case symbol_kind::S_declare_statement: // declare_statement
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_expression_statement: // expression_statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_iteration_statement: // iteration_statement
      case symbol_kind::S_jump_statement: // jump_statement
        value.YY_MOVE_OR_COPY< rvlang::Stmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ASSIGN: // "="
      case symbol_kind::S_MINUS: // "-"
      case symbol_kind::S_PLUS: // "+"
      case symbol_kind::S_STAR: // "*"
      case symbol_kind::S_SLASH: // "/"
      case symbol_kind::S_LPAREN: // "("
      case symbol_kind::S_RPAREN: // ")"
      case symbol_kind::S_LBRACE: // "{"
      case symbol_kind::S_RBRACE: // "}"
      case symbol_kind::S_LBRACKET: // "["
      case symbol_kind::S_RBRACKET: // "]"
      case symbol_kind::S_EQ: // "=="
      case symbol_kind::S_NEQ: // "!="
      case symbol_kind::S_GT: // ">"
      case symbol_kind::S_LT: // "<"
      case symbol_kind::S_GE: // ">="
      case symbol_kind::S_LE: // "<="
      case symbol_kind::S_LOGIC_AND: // "&&"
      case symbol_kind::S_LOGIC_OR: // "||"
      case symbol_kind::S_LOGIC_NOT: // "!"
      case symbol_kind::S_PERCENT: // "%"
      case symbol_kind::S_LSHIFT: // "<<"
      case symbol_kind::S_RSHIFT: // ">>"
      case symbol_kind::S_NOT: // "~"
      case symbol_kind::S_AND: // "&"
      case symbol_kind::S_OR: // "|"
      case symbol_kind::S_XOR: // "^"
      case symbol_kind::S_VOID: // "void"
      case symbol_kind::S_CHAR: // "char"
      case symbol_kind::S_SHORT: // "short"
      case symbol_kind::S_INT: // "int"
      case symbol_kind::S_SIGNED: // "signed"
      case symbol_kind::S_UNSIGNED: // "unsigned"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_IF: // "if"
      case symbol_kind::S_ELSE: // "else"
      case symbol_kind::S_FOR: // "for"
      case symbol_kind::S_WHILE: // "while"
      case symbol_kind::S_SEMICOLON: // ";"
      case symbol_kind::S_COMMA: // ","
      case symbol_kind::S_CONTINUE: // "continue"
      case symbol_kind::S_BREAK: // "break"
      case symbol_kind::S_RETURN: // "return"
      case symbol_kind::S_STRUCT: // "struct"
      case symbol_kind::S_binary_operator: // binary_operator
        value.YY_MOVE_OR_COPY< rvlang::Token > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_elements: // elements
        value.YY_MOVE_OR_COPY< std::vector<int> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration_list: // declaration_list
        value.YY_MOVE_OR_COPY< std::vector<rvlang::Decl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        value.YY_MOVE_OR_COPY< std::vector<rvlang::Expr*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameter_decl_list: // parameter_decl_list
        value.YY_MOVE_OR_COPY< std::vector<rvlang::ParamDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.YY_MOVE_OR_COPY< std::vector<rvlang::Stmt*> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_delaration_specifiers: // delaration_specifiers
      case symbol_kind::S_pointer: // pointer
      case symbol_kind::S_type_specifier: // type_specifier
        value.move< const rvlang::Type* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CONSTANT: // CONSTANT
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_compound_statement: // compound_statement
        value.move< rvlang::CompoundStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_declaration: // declaration
      case symbol_kind::S_function_declaration: // function_declaration
      case symbol_kind::S_array_declaration: // array_declaration
      case symbol_kind::S_variable_declaration: // variable_declaration
        value.move< rvlang::Decl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration_ref_expression: // declaration_ref_expression
        value.move< rvlang::DeclRefExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_array_subscript_expression: // array_subscript_expression
      case symbol_kind::S_unary_expression: // unary_expression
      case symbol_kind::S_dereference_expression: // dereference_expression
      case symbol_kind::S_binary_expression: // binary_expression
      case symbol_kind::S_assignment_expression: // assignment_expression
      case symbol_kind::S_call_expression: // call_expression
      case symbol_kind::S_parameter: // parameter
        value.move< rvlang::Expr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameter_declaration: // parameter_declaration
        value.move< rvlang::ParamDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration_or_statement: // declaration_or_statement
      case symbol_kind::S_declare_statement: // declare_statement
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_expression_statement: // expression_statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_iteration_statement: // iteration_statement
      case symbol_kind::S_jump_statement: // jump_statement
        value.move< rvlang::Stmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ASSIGN: // "="
      case symbol_kind::S_MINUS: // "-"
      case symbol_kind::S_PLUS: // "+"
      case symbol_kind::S_STAR: // "*"
      case symbol_kind::S_SLASH: // "/"
      case symbol_kind::S_LPAREN: // "("
      case symbol_kind::S_RPAREN: // ")"
      case symbol_kind::S_LBRACE: // "{"
      case symbol_kind::S_RBRACE: // "}"
      case symbol_kind::S_LBRACKET: // "["
      case symbol_kind::S_RBRACKET: // "]"
      case symbol_kind::S_EQ: // "=="
      case symbol_kind::S_NEQ: // "!="
      case symbol_kind::S_GT: // ">"
      case symbol_kind::S_LT: // "<"
      case symbol_kind::S_GE: // ">="
      case symbol_kind::S_LE: // "<="
      case symbol_kind::S_LOGIC_AND: // "&&"
      case symbol_kind::S_LOGIC_OR: // "||"
      case symbol_kind::S_LOGIC_NOT: // "!"
      case symbol_kind::S_PERCENT: // "%"
      case symbol_kind::S_LSHIFT: // "<<"
      case symbol_kind::S_RSHIFT: // ">>"
      case symbol_kind::S_NOT: // "~"
      case symbol_kind::S_AND: // "&"
      case symbol_kind::S_OR: // "|"
      case symbol_kind::S_XOR: // "^"
      case symbol_kind::S_VOID: // "void"
      case symbol_kind::S_CHAR: // "char"
      case symbol_kind::S_SHORT: // "short"
      case symbol_kind::S_INT: // "int"
      case symbol_kind::S_SIGNED: // "signed"
      case symbol_kind::S_UNSIGNED: // "unsigned"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_IF: // "if"
      case symbol_kind::S_ELSE: // "else"
      case symbol_kind::S_FOR: // "for"
      case symbol_kind::S_WHILE: // "while"
      case symbol_kind::S_SEMICOLON: // ";"
      case symbol_kind::S_COMMA: // ","
      case symbol_kind::S_CONTINUE: // "continue"
      case symbol_kind::S_BREAK: // "break"
      case symbol_kind::S_RETURN: // "return"
      case symbol_kind::S_STRUCT: // "struct"
      case symbol_kind::S_binary_operator: // binary_operator
        value.move< rvlang::Token > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_elements: // elements
        value.move< std::vector<int> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration_list: // declaration_list
        value.move< std::vector<rvlang::Decl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        value.move< std::vector<rvlang::Expr*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameter_decl_list: // parameter_decl_list
        value.move< std::vector<rvlang::ParamDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.move< std::vector<rvlang::Stmt*> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_delaration_specifiers: // delaration_specifiers
      case symbol_kind::S_pointer: // pointer
      case symbol_kind::S_type_specifier: // type_specifier
        value.copy< const rvlang::Type* > (that.value);
        break;

      case symbol_kind::S_CONSTANT: // CONSTANT
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_compound_statement: // compound_statement
        value.copy< rvlang::CompoundStmt* > (that.value);
        break;

      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_declaration: // declaration
      case symbol_kind::S_function_declaration: // function_declaration
      case symbol_kind::S_array_declaration: // array_declaration
      case symbol_kind::S_variable_declaration: // variable_declaration
        value.copy< rvlang::Decl* > (that.value);
        break;

      case symbol_kind::S_declaration_ref_expression: // declaration_ref_expression
        value.copy< rvlang::DeclRefExpr* > (that.value);
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_array_subscript_expression: // array_subscript_expression
      case symbol_kind::S_unary_expression: // unary_expression
      case symbol_kind::S_dereference_expression: // dereference_expression
      case symbol_kind::S_binary_expression: // binary_expression
      case symbol_kind::S_assignment_expression: // assignment_expression
      case symbol_kind::S_call_expression: // call_expression
      case symbol_kind::S_parameter: // parameter
        value.copy< rvlang::Expr* > (that.value);
        break;

      case symbol_kind::S_parameter_declaration: // parameter_declaration
        value.copy< rvlang::ParamDecl* > (that.value);
        break;

      case symbol_kind::S_declaration_or_statement: // declaration_or_statement
      case symbol_kind::S_declare_statement: // declare_statement
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_expression_statement: // expression_statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_iteration_statement: // iteration_statement
      case symbol_kind::S_jump_statement: // jump_statement
        value.copy< rvlang::Stmt* > (that.value);
        break;

      case symbol_kind::S_ASSIGN: // "="
      case symbol_kind::S_MINUS: // "-"
      case symbol_kind::S_PLUS: // "+"
      case symbol_kind::S_STAR: // "*"
      case symbol_kind::S_SLASH: // "/"
      case symbol_kind::S_LPAREN: // "("
      case symbol_kind::S_RPAREN: // ")"
      case symbol_kind::S_LBRACE: // "{"
      case symbol_kind::S_RBRACE: // "}"
      case symbol_kind::S_LBRACKET: // "["
      case symbol_kind::S_RBRACKET: // "]"
      case symbol_kind::S_EQ: // "=="
      case symbol_kind::S_NEQ: // "!="
      case symbol_kind::S_GT: // ">"
      case symbol_kind::S_LT: // "<"
      case symbol_kind::S_GE: // ">="
      case symbol_kind::S_LE: // "<="
      case symbol_kind::S_LOGIC_AND: // "&&"
      case symbol_kind::S_LOGIC_OR: // "||"
      case symbol_kind::S_LOGIC_NOT: // "!"
      case symbol_kind::S_PERCENT: // "%"
      case symbol_kind::S_LSHIFT: // "<<"
      case symbol_kind::S_RSHIFT: // ">>"
      case symbol_kind::S_NOT: // "~"
      case symbol_kind::S_AND: // "&"
      case symbol_kind::S_OR: // "|"
      case symbol_kind::S_XOR: // "^"
      case symbol_kind::S_VOID: // "void"
      case symbol_kind::S_CHAR: // "char"
      case symbol_kind::S_SHORT: // "short"
      case symbol_kind::S_INT: // "int"
      case symbol_kind::S_SIGNED: // "signed"
      case symbol_kind::S_UNSIGNED: // "unsigned"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_IF: // "if"
      case symbol_kind::S_ELSE: // "else"
      case symbol_kind::S_FOR: // "for"
      case symbol_kind::S_WHILE: // "while"
      case symbol_kind::S_SEMICOLON: // ";"
      case symbol_kind::S_COMMA: // ","
      case symbol_kind::S_CONTINUE: // "continue"
      case symbol_kind::S_BREAK: // "break"
      case symbol_kind::S_RETURN: // "return"
      case symbol_kind::S_STRUCT: // "struct"
      case symbol_kind::S_binary_operator: // binary_operator
        value.copy< rvlang::Token > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_elements: // elements
        value.copy< std::vector<int> > (that.value);
        break;

      case symbol_kind::S_declaration_list: // declaration_list
        value.copy< std::vector<rvlang::Decl*> > (that.value);
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        value.copy< std::vector<rvlang::Expr*> > (that.value);
        break;

      case symbol_kind::S_parameter_decl_list: // parameter_decl_list
        value.copy< std::vector<rvlang::ParamDecl*> > (that.value);
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.copy< std::vector<rvlang::Stmt*> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_delaration_specifiers: // delaration_specifiers
      case symbol_kind::S_pointer: // pointer
      case symbol_kind::S_type_specifier: // type_specifier
        value.move< const rvlang::Type* > (that.value);
        break;

      case symbol_kind::S_CONSTANT: // CONSTANT
        value.move< int > (that.value);
        break;

      case symbol_kind::S_compound_statement: // compound_statement
        value.move< rvlang::CompoundStmt* > (that.value);
        break;

      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_declaration: // declaration
      case symbol_kind::S_function_declaration: // function_declaration
      case symbol_kind::S_array_declaration: // array_declaration
      case symbol_kind::S_variable_declaration: // variable_declaration
        value.move< rvlang::Decl* > (that.value);
        break;

      case symbol_kind::S_declaration_ref_expression: // declaration_ref_expression
        value.move< rvlang::DeclRefExpr* > (that.value);
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_array_subscript_expression: // array_subscript_expression
      case symbol_kind::S_unary_expression: // unary_expression
      case symbol_kind::S_dereference_expression: // dereference_expression
      case symbol_kind::S_binary_expression: // binary_expression
      case symbol_kind::S_assignment_expression: // assignment_expression
      case symbol_kind::S_call_expression: // call_expression
      case symbol_kind::S_parameter: // parameter
        value.move< rvlang::Expr* > (that.value);
        break;

      case symbol_kind::S_parameter_declaration: // parameter_declaration
        value.move< rvlang::ParamDecl* > (that.value);
        break;

      case symbol_kind::S_declaration_or_statement: // declaration_or_statement
      case symbol_kind::S_declare_statement: // declare_statement
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_expression_statement: // expression_statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_iteration_statement: // iteration_statement
      case symbol_kind::S_jump_statement: // jump_statement
        value.move< rvlang::Stmt* > (that.value);
        break;

      case symbol_kind::S_ASSIGN: // "="
      case symbol_kind::S_MINUS: // "-"
      case symbol_kind::S_PLUS: // "+"
      case symbol_kind::S_STAR: // "*"
      case symbol_kind::S_SLASH: // "/"
      case symbol_kind::S_LPAREN: // "("
      case symbol_kind::S_RPAREN: // ")"
      case symbol_kind::S_LBRACE: // "{"
      case symbol_kind::S_RBRACE: // "}"
      case symbol_kind::S_LBRACKET: // "["
      case symbol_kind::S_RBRACKET: // "]"
      case symbol_kind::S_EQ: // "=="
      case symbol_kind::S_NEQ: // "!="
      case symbol_kind::S_GT: // ">"
      case symbol_kind::S_LT: // "<"
      case symbol_kind::S_GE: // ">="
      case symbol_kind::S_LE: // "<="
      case symbol_kind::S_LOGIC_AND: // "&&"
      case symbol_kind::S_LOGIC_OR: // "||"
      case symbol_kind::S_LOGIC_NOT: // "!"
      case symbol_kind::S_PERCENT: // "%"
      case symbol_kind::S_LSHIFT: // "<<"
      case symbol_kind::S_RSHIFT: // ">>"
      case symbol_kind::S_NOT: // "~"
      case symbol_kind::S_AND: // "&"
      case symbol_kind::S_OR: // "|"
      case symbol_kind::S_XOR: // "^"
      case symbol_kind::S_VOID: // "void"
      case symbol_kind::S_CHAR: // "char"
      case symbol_kind::S_SHORT: // "short"
      case symbol_kind::S_INT: // "int"
      case symbol_kind::S_SIGNED: // "signed"
      case symbol_kind::S_UNSIGNED: // "unsigned"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_IF: // "if"
      case symbol_kind::S_ELSE: // "else"
      case symbol_kind::S_FOR: // "for"
      case symbol_kind::S_WHILE: // "while"
      case symbol_kind::S_SEMICOLON: // ";"
      case symbol_kind::S_COMMA: // ","
      case symbol_kind::S_CONTINUE: // "continue"
      case symbol_kind::S_BREAK: // "break"
      case symbol_kind::S_RETURN: // "return"
      case symbol_kind::S_STRUCT: // "struct"
      case symbol_kind::S_binary_operator: // binary_operator
        value.move< rvlang::Token > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_elements: // elements
        value.move< std::vector<int> > (that.value);
        break;

      case symbol_kind::S_declaration_list: // declaration_list
        value.move< std::vector<rvlang::Decl*> > (that.value);
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        value.move< std::vector<rvlang::Expr*> > (that.value);
        break;

      case symbol_kind::S_parameter_decl_list: // parameter_decl_list
        value.move< std::vector<rvlang::ParamDecl*> > (that.value);
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.move< std::vector<rvlang::Stmt*> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // Discard the LAC context in case there still is one left from a
    // previous invocation.
    yy_lac_discard_ ("init");

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (compiler));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        if (!yy_lac_establish_ (yyla.kind ()))
          goto yyerrlab;
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        if (!yy_lac_establish_ (yyla.kind ()))
          goto yyerrlab;

        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    yy_lac_discard_ ("shift");
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_delaration_specifiers: // delaration_specifiers
      case symbol_kind::S_pointer: // pointer
      case symbol_kind::S_type_specifier: // type_specifier
        yylhs.value.emplace< const rvlang::Type* > ();
        break;

      case symbol_kind::S_CONSTANT: // CONSTANT
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_compound_statement: // compound_statement
        yylhs.value.emplace< rvlang::CompoundStmt* > ();
        break;

      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_declaration: // declaration
      case symbol_kind::S_function_declaration: // function_declaration
      case symbol_kind::S_array_declaration: // array_declaration
      case symbol_kind::S_variable_declaration: // variable_declaration
        yylhs.value.emplace< rvlang::Decl* > ();
        break;

      case symbol_kind::S_declaration_ref_expression: // declaration_ref_expression
        yylhs.value.emplace< rvlang::DeclRefExpr* > ();
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_array_subscript_expression: // array_subscript_expression
      case symbol_kind::S_unary_expression: // unary_expression
      case symbol_kind::S_dereference_expression: // dereference_expression
      case symbol_kind::S_binary_expression: // binary_expression
      case symbol_kind::S_assignment_expression: // assignment_expression
      case symbol_kind::S_call_expression: // call_expression
      case symbol_kind::S_parameter: // parameter
        yylhs.value.emplace< rvlang::Expr* > ();
        break;

      case symbol_kind::S_parameter_declaration: // parameter_declaration
        yylhs.value.emplace< rvlang::ParamDecl* > ();
        break;

      case symbol_kind::S_declaration_or_statement: // declaration_or_statement
      case symbol_kind::S_declare_statement: // declare_statement
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_expression_statement: // expression_statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_iteration_statement: // iteration_statement
      case symbol_kind::S_jump_statement: // jump_statement
        yylhs.value.emplace< rvlang::Stmt* > ();
        break;

      case symbol_kind::S_ASSIGN: // "="
      case symbol_kind::S_MINUS: // "-"
      case symbol_kind::S_PLUS: // "+"
      case symbol_kind::S_STAR: // "*"
      case symbol_kind::S_SLASH: // "/"
      case symbol_kind::S_LPAREN: // "("
      case symbol_kind::S_RPAREN: // ")"
      case symbol_kind::S_LBRACE: // "{"
      case symbol_kind::S_RBRACE: // "}"
      case symbol_kind::S_LBRACKET: // "["
      case symbol_kind::S_RBRACKET: // "]"
      case symbol_kind::S_EQ: // "=="
      case symbol_kind::S_NEQ: // "!="
      case symbol_kind::S_GT: // ">"
      case symbol_kind::S_LT: // "<"
      case symbol_kind::S_GE: // ">="
      case symbol_kind::S_LE: // "<="
      case symbol_kind::S_LOGIC_AND: // "&&"
      case symbol_kind::S_LOGIC_OR: // "||"
      case symbol_kind::S_LOGIC_NOT: // "!"
      case symbol_kind::S_PERCENT: // "%"
      case symbol_kind::S_LSHIFT: // "<<"
      case symbol_kind::S_RSHIFT: // ">>"
      case symbol_kind::S_NOT: // "~"
      case symbol_kind::S_AND: // "&"
      case symbol_kind::S_OR: // "|"
      case symbol_kind::S_XOR: // "^"
      case symbol_kind::S_VOID: // "void"
      case symbol_kind::S_CHAR: // "char"
      case symbol_kind::S_SHORT: // "short"
      case symbol_kind::S_INT: // "int"
      case symbol_kind::S_SIGNED: // "signed"
      case symbol_kind::S_UNSIGNED: // "unsigned"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_IF: // "if"
      case symbol_kind::S_ELSE: // "else"
      case symbol_kind::S_FOR: // "for"
      case symbol_kind::S_WHILE: // "while"
      case symbol_kind::S_SEMICOLON: // ";"
      case symbol_kind::S_COMMA: // ","
      case symbol_kind::S_CONTINUE: // "continue"
      case symbol_kind::S_BREAK: // "break"
      case symbol_kind::S_RETURN: // "return"
      case symbol_kind::S_STRUCT: // "struct"
      case symbol_kind::S_binary_operator: // binary_operator
        yylhs.value.emplace< rvlang::Token > ();
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_elements: // elements
        yylhs.value.emplace< std::vector<int> > ();
        break;

      case symbol_kind::S_declaration_list: // declaration_list
        yylhs.value.emplace< std::vector<rvlang::Decl*> > ();
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        yylhs.value.emplace< std::vector<rvlang::Expr*> > ();
        break;

      case symbol_kind::S_parameter_decl_list: // parameter_decl_list
        yylhs.value.emplace< std::vector<rvlang::ParamDecl*> > ();
        break;

      case symbol_kind::S_statement_list: // statement_list
        yylhs.value.emplace< std::vector<rvlang::Stmt*> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // translation_unit: declaration_list
#line 154 "rvlang.yy"
                     {
      auto* unit = compiler.getTranslationUnit();
      for(auto* d: yystack_[0].value.as < std::vector<rvlang::Decl*> > ()) {
        unit->addDecl(d);
      }
    }
#line 1172 "Parser.cpp"
    break;

  case 3: // declaration_list: declaration
#line 162 "rvlang.yy"
                              {
      yylhs.value.as < std::vector<rvlang::Decl*> > () = std::vector<rvlang::Decl*>();
      yylhs.value.as < std::vector<rvlang::Decl*> > ().push_back(yystack_[0].value.as < rvlang::Decl* > ());
    }
#line 1181 "Parser.cpp"
    break;

  case 4: // declaration_list: declaration_list declaration
#line 166 "rvlang.yy"
                                 {
      yystack_[1].value.as < std::vector<rvlang::Decl*> > ().push_back(yystack_[0].value.as < rvlang::Decl* > ());
      yylhs.value.as < std::vector<rvlang::Decl*> > () = std::move(yystack_[1].value.as < std::vector<rvlang::Decl*> > ());
    }
#line 1190 "Parser.cpp"
    break;

  case 5: // declaration: function_declaration
#line 172 "rvlang.yy"
                                  { yylhs.value.as < rvlang::Decl* > () = yystack_[0].value.as < rvlang::Decl* > (); }
#line 1196 "Parser.cpp"
    break;

  case 6: // declaration: variable_declaration
#line 173 "rvlang.yy"
                         { yylhs.value.as < rvlang::Decl* > () = yystack_[0].value.as < rvlang::Decl* > (); }
#line 1202 "Parser.cpp"
    break;

  case 7: // declaration: array_declaration
#line 174 "rvlang.yy"
                      { yylhs.value.as < rvlang::Decl* > () = yystack_[0].value.as < rvlang::Decl* > (); }
#line 1208 "Parser.cpp"
    break;

  case 8: // function_declaration: delaration_specifiers IDENTIFIER "(" parameter_decl_list ")" ";"
#line 178 "rvlang.yy"
                                                                     {
      yylhs.value.as < rvlang::Decl* > () = compiler.getAstContext()->newNode<rvlang::FunctionDecl>(compiler.location(), yystack_[5].value.as < const rvlang::Type* > (), yystack_[4].value.as < std::string > (), std::move(yystack_[2].value.as < std::vector<rvlang::ParamDecl*> > ()));
    }
#line 1216 "Parser.cpp"
    break;

  case 9: // function_declaration: delaration_specifiers IDENTIFIER "(" parameter_decl_list ")" compound_statement
#line 181 "rvlang.yy"
                                                                                    {
      yylhs.value.as < rvlang::Decl* > () = compiler.getAstContext()->newNode<rvlang::FunctionDecl>(compiler.location(), yystack_[5].value.as < const rvlang::Type* > (), yystack_[4].value.as < std::string > (), std::move(yystack_[2].value.as < std::vector<rvlang::ParamDecl*> > ()), yystack_[0].value.as < rvlang::CompoundStmt* > ());
    }
#line 1224 "Parser.cpp"
    break;

  case 10: // array_declaration: delaration_specifiers IDENTIFIER "[" CONSTANT "]" ";"
#line 187 "rvlang.yy"
                                                          {
      std::string arrayTypeName = "(" + yystack_[5].value.as < const rvlang::Type* > ()->getName() + ")*";
      auto* t = compiler.getAstContext()->getNamedType(arrayTypeName);
      if (t == nullptr) {
        t = compiler.getAstContext()->newType<rvlang::PointerType>(arrayTypeName, yystack_[5].value.as < const rvlang::Type* > ());
      }
      yylhs.value.as < rvlang::Decl* > () = compiler.getAstContext()->newNode<rvlang::ArrayDecl>(compiler.location(), yystack_[4].value.as < std::string > (), t, yystack_[5].value.as < const rvlang::Type* > (), yystack_[2].value.as < int > ());
    }
#line 1237 "Parser.cpp"
    break;

  case 11: // array_declaration: delaration_specifiers IDENTIFIER "[" CONSTANT "]" "=" "{" elements "}" ";"
#line 195 "rvlang.yy"
                                                                               {
      if (yystack_[6].value.as < int > () != yystack_[2].value.as < std::vector<int> > ().size()) {
        throw yy::parser::syntax_error(compiler.location(), "array size doesn't match");
      }
      std::string arrayTypeName = "(" + yystack_[9].value.as < const rvlang::Type* > ()->getName() + ")*";
      auto* t = compiler.getAstContext()->getNamedType(arrayTypeName);
      if (t == nullptr) {
        t = compiler.getAstContext()->newType<rvlang::PointerType>(arrayTypeName, yystack_[9].value.as < const rvlang::Type* > ());
      }
      yylhs.value.as < rvlang::Decl* > () = compiler.getAstContext()->newNode<rvlang::ArrayDecl>(compiler.location(), yystack_[8].value.as < std::string > (), t, yystack_[9].value.as < const rvlang::Type* > (), yystack_[6].value.as < int > (), yystack_[2].value.as < std::vector<int> > ());
    }
#line 1253 "Parser.cpp"
    break;

  case 12: // elements: CONSTANT
#line 209 "rvlang.yy"
             {
      yylhs.value.as < std::vector<int> > () = std::vector<int>();
      yylhs.value.as < std::vector<int> > ().push_back(yystack_[0].value.as < int > ());
    }
#line 1262 "Parser.cpp"
    break;

  case 13: // elements: elements "," CONSTANT
#line 213 "rvlang.yy"
                          {
      yystack_[2].value.as < std::vector<int> > ().push_back(yystack_[0].value.as < int > ());
      yylhs.value.as < std::vector<int> > () = std::move(yystack_[2].value.as < std::vector<int> > ());
    }
#line 1271 "Parser.cpp"
    break;

  case 14: // delaration_specifiers: type_specifier
#line 221 "rvlang.yy"
                   { yylhs.value.as < const rvlang::Type* > () = yystack_[0].value.as < const rvlang::Type* > (); }
#line 1277 "Parser.cpp"
    break;

  case 15: // delaration_specifiers: pointer
#line 222 "rvlang.yy"
            { yylhs.value.as < const rvlang::Type* > () = yystack_[0].value.as < const rvlang::Type* > (); }
#line 1283 "Parser.cpp"
    break;

  case 16: // pointer: type_specifier "*"
#line 226 "rvlang.yy"
                       {
      std::string typeName = "(" + yystack_[1].value.as < const rvlang::Type* > ()->getName() + ")*";
      auto* t = compiler.getAstContext()->getNamedType(typeName);
      if (t == nullptr) {
        t = compiler.getAstContext()->newType<rvlang::PointerType>(typeName, yystack_[1].value.as < const rvlang::Type* > ());
      }
      yylhs.value.as < const rvlang::Type* > () = t;
    }
#line 1296 "Parser.cpp"
    break;

  case 17: // pointer: pointer "*"
#line 234 "rvlang.yy"
                {
      std::string typeName = "(" + yystack_[1].value.as < const rvlang::Type* > ()->getName() + ")*";
      auto* t = compiler.getAstContext()->getNamedType(typeName);
      if (t == nullptr) {
        t = compiler.getAstContext()->newType<rvlang::PointerType>(typeName, yystack_[1].value.as < const rvlang::Type* > ());
      }
      yylhs.value.as < const rvlang::Type* > () = t;
    }
#line 1309 "Parser.cpp"
    break;

  case 18: // type_specifier: "void"
#line 245 "rvlang.yy"
           {
      yylhs.value.as < const rvlang::Type* > () = compiler.getAstContext()->newType<rvlang::VoidType>();
    }
#line 1317 "Parser.cpp"
    break;

  case 19: // type_specifier: "char"
#line 248 "rvlang.yy"
           {
      yylhs.value.as < const rvlang::Type* > () = compiler.getAstContext()->newType<rvlang::IntegerType>("char", 1, true);
    }
#line 1325 "Parser.cpp"
    break;

  case 20: // type_specifier: "short"
#line 251 "rvlang.yy"
            {
      yylhs.value.as < const rvlang::Type* > () = compiler.getAstContext()->newType<rvlang::IntegerType>("short", 2, true);
    }
#line 1333 "Parser.cpp"
    break;

  case 21: // type_specifier: "int"
#line 254 "rvlang.yy"
          {
      yylhs.value.as < const rvlang::Type* > () = compiler.getAstContext()->newType<rvlang::IntegerType>("int", 4, true);
    }
#line 1341 "Parser.cpp"
    break;

  case 22: // type_specifier: "long"
#line 257 "rvlang.yy"
           {
      yylhs.value.as < const rvlang::Type* > () = compiler.getAstContext()->newType<rvlang::IntegerType>("long", 8, true);
    }
#line 1349 "Parser.cpp"
    break;

  case 23: // type_specifier: "float"
#line 260 "rvlang.yy"
            {
      yylhs.value.as < const rvlang::Type* > () = compiler.getAstContext()->newType<rvlang::FloatPointType>();
    }
#line 1357 "Parser.cpp"
    break;

  case 24: // type_specifier: "unsigned" "char"
#line 263 "rvlang.yy"
                      {
      yylhs.value.as < const rvlang::Type* > () = compiler.getAstContext()->newType<rvlang::IntegerType>("char", 1, false);
    }
#line 1365 "Parser.cpp"
    break;

  case 25: // type_specifier: "unsigned" "short"
#line 266 "rvlang.yy"
                       {
      yylhs.value.as < const rvlang::Type* > () = compiler.getAstContext()->newType<rvlang::IntegerType>("short", 2, false);
    }
#line 1373 "Parser.cpp"
    break;

  case 26: // type_specifier: "unsigned" "int"
#line 269 "rvlang.yy"
                     {
      yylhs.value.as < const rvlang::Type* > () = compiler.getAstContext()->newType<rvlang::IntegerType>("int", 4, false);
    }
#line 1381 "Parser.cpp"
    break;

  case 27: // type_specifier: "unsigned" "long"
#line 272 "rvlang.yy"
                      {
      yylhs.value.as < const rvlang::Type* > () = compiler.getAstContext()->newType<rvlang::IntegerType>("long", 8, false);
    }
#line 1389 "Parser.cpp"
    break;

  case 28: // parameter_decl_list: %empty
#line 278 "rvlang.yy"
    { yylhs.value.as < std::vector<rvlang::ParamDecl*> > () = std::vector<rvlang::ParamDecl*>(); }
#line 1395 "Parser.cpp"
    break;

  case 29: // parameter_decl_list: parameter_declaration
#line 279 "rvlang.yy"
                          { 
      yylhs.value.as < std::vector<rvlang::ParamDecl*> > () = std::vector<rvlang::ParamDecl*>();
      yylhs.value.as < std::vector<rvlang::ParamDecl*> > ().push_back(yystack_[0].value.as < rvlang::ParamDecl* > ());
    }
#line 1404 "Parser.cpp"
    break;

  case 30: // parameter_decl_list: parameter_decl_list "," parameter_declaration
#line 283 "rvlang.yy"
                                                  {
      yystack_[2].value.as < std::vector<rvlang::ParamDecl*> > ().push_back(yystack_[0].value.as < rvlang::ParamDecl* > ());
      yylhs.value.as < std::vector<rvlang::ParamDecl*> > () = std::move(yystack_[2].value.as < std::vector<rvlang::ParamDecl*> > ());
    }
#line 1413 "Parser.cpp"
    break;

  case 31: // parameter_declaration: delaration_specifiers IDENTIFIER
#line 290 "rvlang.yy"
                                     {
      yylhs.value.as < rvlang::ParamDecl* > () = compiler.getAstContext()->newNode<rvlang::ParamDecl>(compiler.location(), yystack_[1].value.as < const rvlang::Type* > (), yystack_[0].value.as < std::string > ());
    }
#line 1421 "Parser.cpp"
    break;

  case 32: // compound_statement: "{" statement_list "}"
#line 296 "rvlang.yy"
                           {
      yylhs.value.as < rvlang::CompoundStmt* > () = compiler.getAstContext()->newNode<rvlang::CompoundStmt>(compiler.location(), std::move(yystack_[1].value.as < std::vector<rvlang::Stmt*> > ()));
    }
#line 1429 "Parser.cpp"
    break;

  case 33: // compound_statement: "{" "}"
#line 299 "rvlang.yy"
            { yylhs.value.as < rvlang::CompoundStmt* > () = compiler.getAstContext()->newNode<rvlang::CompoundStmt>(compiler.location()); }
#line 1435 "Parser.cpp"
    break;

  case 34: // statement_list: declaration_or_statement
#line 303 "rvlang.yy"
                             {
      yylhs.value.as < std::vector<rvlang::Stmt*> > () = std::vector<rvlang::Stmt*>();
      yylhs.value.as < std::vector<rvlang::Stmt*> > ().push_back(yystack_[0].value.as < rvlang::Stmt* > ());
    }
#line 1444 "Parser.cpp"
    break;

  case 35: // statement_list: statement_list declaration_or_statement
#line 307 "rvlang.yy"
                                            {
      yystack_[1].value.as < std::vector<rvlang::Stmt*> > ().push_back(yystack_[0].value.as < rvlang::Stmt* > ());
      yylhs.value.as < std::vector<rvlang::Stmt*> > () = std::move(yystack_[1].value.as < std::vector<rvlang::Stmt*> > ());
    }
#line 1453 "Parser.cpp"
    break;

  case 36: // declaration_or_statement: statement
#line 314 "rvlang.yy"
                { yylhs.value.as < rvlang::Stmt* > () = yystack_[0].value.as < rvlang::Stmt* > (); }
#line 1459 "Parser.cpp"
    break;

  case 37: // declaration_or_statement: declare_statement
#line 315 "rvlang.yy"
                      { yylhs.value.as < rvlang::Stmt* > () = yystack_[0].value.as < rvlang::Stmt* > (); }
#line 1465 "Parser.cpp"
    break;

  case 38: // declare_statement: variable_declaration
#line 318 "rvlang.yy"
                                        { yylhs.value.as < rvlang::Stmt* > () = compiler.getAstContext()->newNode<rvlang::DeclStmt>(compiler.location(), yystack_[0].value.as < rvlang::Decl* > ()); }
#line 1471 "Parser.cpp"
    break;

  case 39: // variable_declaration: delaration_specifiers IDENTIFIER ";"
#line 322 "rvlang.yy"
                                         {
      yylhs.value.as < rvlang::Decl* > () = compiler.getAstContext()->newNode<rvlang::VarDecl>(compiler.location(), yystack_[2].value.as < const rvlang::Type* > (), yystack_[1].value.as < std::string > ());
    }
#line 1479 "Parser.cpp"
    break;

  case 40: // variable_declaration: delaration_specifiers IDENTIFIER "=" expression ";"
#line 325 "rvlang.yy"
                                                        {
      yylhs.value.as < rvlang::Decl* > () = compiler.getAstContext()->newNode<rvlang::VarDecl>(compiler.location(), yystack_[4].value.as < const rvlang::Type* > (), yystack_[3].value.as < std::string > (), yystack_[1].value.as < rvlang::Expr* > ());
    }
#line 1487 "Parser.cpp"
    break;

  case 41: // expression: CONSTANT
#line 331 "rvlang.yy"
             {
      auto* intType = compiler.getAstContext()->getNamedType("int");
      if (intType == nullptr) {
        intType = compiler.getAstContext()->newType<rvlang::IntegerType>("int", 4, true);
      }
      yylhs.value.as < rvlang::Expr* > () = compiler.getAstContext()->newNode<rvlang::Constant>(compiler.location(), yystack_[0].value.as < int > (), intType); 
    }
#line 1499 "Parser.cpp"
    break;

  case 42: // expression: STRING_LITERAL
#line 338 "rvlang.yy"
                   {
      auto* charType = compiler.getAstContext()->getNamedType("char");
      if(charType == nullptr) {
        charType = compiler.getAstContext()->newType<rvlang::IntegerType>("char", 1, true);
      }
      auto* stringType = compiler.getAstContext()->getNamedType("(char)*");
      if (stringType == nullptr) {
        stringType = compiler.getAstContext()->newType<rvlang::PointerType>("(char)*", charType);
      }
      yylhs.value.as < rvlang::Expr* > () = compiler.getAstContext()->newNode<rvlang::StringLiteral>(compiler.location(), yystack_[0].value.as < std::string > (), nullptr);
    }
#line 1515 "Parser.cpp"
    break;

  case 43: // expression: declaration_ref_expression
#line 349 "rvlang.yy"
                               { yylhs.value.as < rvlang::Expr* > () = yystack_[0].value.as < rvlang::DeclRefExpr* > (); }
#line 1521 "Parser.cpp"
    break;

  case 44: // expression: unary_expression
#line 350 "rvlang.yy"
                      { yylhs.value.as < rvlang::Expr* > () = yystack_[0].value.as < rvlang::Expr* > (); }
#line 1527 "Parser.cpp"
    break;

  case 45: // expression: binary_expression
#line 351 "rvlang.yy"
                      { yylhs.value.as < rvlang::Expr* > () = yystack_[0].value.as < rvlang::Expr* > (); }
#line 1533 "Parser.cpp"
    break;

  case 46: // expression: call_expression
#line 352 "rvlang.yy"
                      { yylhs.value.as < rvlang::Expr* > () = yystack_[0].value.as < rvlang::Expr* > (); }
#line 1539 "Parser.cpp"
    break;

  case 47: // expression: "(" expression ")"
#line 353 "rvlang.yy"
                        { yylhs.value.as < rvlang::Expr* > () = yystack_[1].value.as < rvlang::Expr* > (); }
#line 1545 "Parser.cpp"
    break;

  case 48: // expression: "(" delaration_specifiers ")" expression
#line 354 "rvlang.yy"
                                             {
      yylhs.value.as < rvlang::Expr* > () = compiler.getAstContext()->newNode<rvlang::CastExpr>(compiler.location(), yystack_[0].value.as < rvlang::Expr* > (), nullptr, yystack_[2].value.as < const rvlang::Type* > ());
    }
#line 1553 "Parser.cpp"
    break;

  case 49: // expression: array_subscript_expression
#line 357 "rvlang.yy"
                               { yylhs.value.as < rvlang::Expr* > () = yystack_[0].value.as < rvlang::Expr* > (); }
#line 1559 "Parser.cpp"
    break;

  case 50: // declaration_ref_expression: IDENTIFIER
#line 361 "rvlang.yy"
               {
      yylhs.value.as < rvlang::DeclRefExpr* > () = compiler.getAstContext()->newNode<rvlang::DeclRefExpr>(compiler.location(), yystack_[0].value.as < std::string > (), nullptr);
    }
#line 1567 "Parser.cpp"
    break;

  case 51: // array_subscript_expression: declaration_ref_expression "[" expression "]"
#line 367 "rvlang.yy"
                                                  {
      yylhs.value.as < rvlang::Expr* > () = compiler.getAstContext()->newNode<rvlang::ArraySubscriptExpr>(compiler.location(), yystack_[3].value.as < rvlang::DeclRefExpr* > (), yystack_[1].value.as < rvlang::Expr* > ());
    }
#line 1575 "Parser.cpp"
    break;

  case 52: // unary_expression: "!" expression
#line 373 "rvlang.yy"
                   {
      yylhs.value.as < rvlang::Expr* > () = compiler.getAstContext()->newNode<rvlang::UnaryExpr>(compiler.location(), yystack_[1].value.as < rvlang::Token > (), yystack_[0].value.as < rvlang::Expr* > (), nullptr);
    }
#line 1583 "Parser.cpp"
    break;

  case 53: // unary_expression: "~" expression
#line 376 "rvlang.yy"
                    { yylhs.value.as < rvlang::Expr* > () = compiler.getAstContext()->newNode<rvlang::UnaryExpr>(compiler.location(), yystack_[1].value.as < rvlang::Token > (), yystack_[0].value.as < rvlang::Expr* > (), nullptr); }
#line 1589 "Parser.cpp"
    break;

  case 54: // unary_expression: "&" expression
#line 377 "rvlang.yy"
                    {
      yylhs.value.as < rvlang::Expr* > () = compiler.getAstContext()->newNode<rvlang::UnaryExpr>(compiler.location(), yystack_[1].value.as < rvlang::Token > (), yystack_[0].value.as < rvlang::Expr* > (), nullptr);
    }
#line 1597 "Parser.cpp"
    break;

  case 55: // unary_expression: dereference_expression
#line 380 "rvlang.yy"
                           { yylhs.value.as < rvlang::Expr* > () = yystack_[0].value.as < rvlang::Expr* > (); }
#line 1603 "Parser.cpp"
    break;

  case 56: // dereference_expression: "*" expression
#line 384 "rvlang.yy"
                    { yylhs.value.as < rvlang::Expr* > () = compiler.getAstContext()->newNode<rvlang::UnaryExpr>(compiler.location(), yystack_[1].value.as < rvlang::Token > (), yystack_[0].value.as < rvlang::Expr* > (), nullptr); }
#line 1609 "Parser.cpp"
    break;

  case 57: // binary_expression: expression binary_operator expression
#line 388 "rvlang.yy"
                                          {
      yylhs.value.as < rvlang::Expr* > () = compiler.getAstContext()->newNode<rvlang::BinaryExpr>(compiler.location(), yystack_[1].value.as < rvlang::Token > (), yystack_[2].value.as < rvlang::Expr* > (), yystack_[0].value.as < rvlang::Expr* > (), nullptr);
    }
#line 1617 "Parser.cpp"
    break;

  case 58: // binary_operator: "+"
#line 394 "rvlang.yy"
        { yylhs.value.as < rvlang::Token > () = yystack_[0].value.as < rvlang::Token > (); }
#line 1623 "Parser.cpp"
    break;

  case 59: // binary_operator: "-"
#line 395 "rvlang.yy"
        { yylhs.value.as < rvlang::Token > () = yystack_[0].value.as < rvlang::Token > (); }
#line 1629 "Parser.cpp"
    break;

  case 60: // binary_operator: "*"
#line 396 "rvlang.yy"
        { yylhs.value.as < rvlang::Token > () = yystack_[0].value.as < rvlang::Token > (); }
#line 1635 "Parser.cpp"
    break;

  case 61: // binary_operator: "/"
#line 397 "rvlang.yy"
        { yylhs.value.as < rvlang::Token > () = yystack_[0].value.as < rvlang::Token > (); }
#line 1641 "Parser.cpp"
    break;

  case 62: // binary_operator: "%"
#line 398 "rvlang.yy"
        { yylhs.value.as < rvlang::Token > () = yystack_[0].value.as < rvlang::Token > (); }
#line 1647 "Parser.cpp"
    break;

  case 63: // binary_operator: "<<"
#line 399 "rvlang.yy"
         { yylhs.value.as < rvlang::Token > () = yystack_[0].value.as < rvlang::Token > (); }
#line 1653 "Parser.cpp"
    break;

  case 64: // binary_operator: ">>"
#line 400 "rvlang.yy"
         { yylhs.value.as < rvlang::Token > () = yystack_[0].value.as < rvlang::Token > (); }
#line 1659 "Parser.cpp"
    break;

  case 65: // binary_operator: "=="
#line 401 "rvlang.yy"
         { yylhs.value.as < rvlang::Token > () = yystack_[0].value.as < rvlang::Token > (); }
#line 1665 "Parser.cpp"
    break;

  case 66: // binary_operator: "!="
#line 402 "rvlang.yy"
         { yylhs.value.as < rvlang::Token > () = yystack_[0].value.as < rvlang::Token > (); }
#line 1671 "Parser.cpp"
    break;

  case 67: // binary_operator: ">="
#line 403 "rvlang.yy"
         { yylhs.value.as < rvlang::Token > () = yystack_[0].value.as < rvlang::Token > (); }
#line 1677 "Parser.cpp"
    break;

  case 68: // binary_operator: "<="
#line 404 "rvlang.yy"
         { yylhs.value.as < rvlang::Token > () = yystack_[0].value.as < rvlang::Token > (); }
#line 1683 "Parser.cpp"
    break;

  case 69: // binary_operator: ">"
#line 405 "rvlang.yy"
        { yylhs.value.as < rvlang::Token > () = yystack_[0].value.as < rvlang::Token > (); }
#line 1689 "Parser.cpp"
    break;

  case 70: // binary_operator: "<"
#line 406 "rvlang.yy"
        { yylhs.value.as < rvlang::Token > () = yystack_[0].value.as < rvlang::Token > (); }
#line 1695 "Parser.cpp"
    break;

  case 71: // binary_operator: "&&"
#line 407 "rvlang.yy"
         { yylhs.value.as < rvlang::Token > () = yystack_[0].value.as < rvlang::Token > (); }
#line 1701 "Parser.cpp"
    break;

  case 72: // binary_operator: "||"
#line 408 "rvlang.yy"
         { yylhs.value.as < rvlang::Token > () = yystack_[0].value.as < rvlang::Token > (); }
#line 1707 "Parser.cpp"
    break;

  case 73: // binary_operator: "&"
#line 409 "rvlang.yy"
        { yylhs.value.as < rvlang::Token > () = yystack_[0].value.as < rvlang::Token > (); }
#line 1713 "Parser.cpp"
    break;

  case 74: // binary_operator: "|"
#line 410 "rvlang.yy"
        { yylhs.value.as < rvlang::Token > () = yystack_[0].value.as < rvlang::Token > (); }
#line 1719 "Parser.cpp"
    break;

  case 75: // binary_operator: "^"
#line 411 "rvlang.yy"
        { yylhs.value.as < rvlang::Token > () = yystack_[0].value.as < rvlang::Token > (); }
#line 1725 "Parser.cpp"
    break;

  case 76: // statement: expression_statement
#line 415 "rvlang.yy"
                         { yylhs.value.as < rvlang::Stmt* > () = yystack_[0].value.as < rvlang::Stmt* > (); }
#line 1731 "Parser.cpp"
    break;

  case 77: // statement: selection_statement
#line 416 "rvlang.yy"
                        { yylhs.value.as < rvlang::Stmt* > () = yystack_[0].value.as < rvlang::Stmt* > (); }
#line 1737 "Parser.cpp"
    break;

  case 78: // statement: iteration_statement
#line 417 "rvlang.yy"
                        { yylhs.value.as < rvlang::Stmt* > () = yystack_[0].value.as < rvlang::Stmt* > (); }
#line 1743 "Parser.cpp"
    break;

  case 79: // statement: jump_statement
#line 418 "rvlang.yy"
                    { yylhs.value.as < rvlang::Stmt* > () = yystack_[0].value.as < rvlang::Stmt* > (); }
#line 1749 "Parser.cpp"
    break;

  case 80: // expression_statement: assignment_expression
#line 421 "rvlang.yy"
                                            { yylhs.value.as < rvlang::Stmt* > () = yystack_[0].value.as < rvlang::Expr* > (); }
#line 1755 "Parser.cpp"
    break;

  case 81: // expression_statement: call_expression ";"
#line 422 "rvlang.yy"
                        { yylhs.value.as < rvlang::Stmt* > () = yystack_[1].value.as < rvlang::Expr* > (); }
#line 1761 "Parser.cpp"
    break;

  case 82: // assignment_expression: dereference_expression "=" expression ";"
#line 426 "rvlang.yy"
                                              {
      //auto* declRef = compiler.getAstContext()->newNode<rvlang::DeclRefExpr>(compiler.location(), $1, nullptr);
      yylhs.value.as < rvlang::Expr* > () = compiler.getAstContext()->newNode<rvlang::BinaryExpr>(compiler.location(), yystack_[2].value.as < rvlang::Token > (), yystack_[3].value.as < rvlang::Expr* > (), yystack_[1].value.as < rvlang::Expr* > (), nullptr);
    }
#line 1770 "Parser.cpp"
    break;

  case 83: // assignment_expression: declaration_ref_expression "=" expression ";"
#line 431 "rvlang.yy"
                                                  {
      //auto* declRef = compiler.getAstContext()->newNode<rvlang::DeclRefExpr>(compiler.location(), $1, nullptr);
      yylhs.value.as < rvlang::Expr* > () = compiler.getAstContext()->newNode<rvlang::BinaryExpr>(compiler.location(), yystack_[2].value.as < rvlang::Token > (), yystack_[3].value.as < rvlang::DeclRefExpr* > (), yystack_[1].value.as < rvlang::Expr* > (), nullptr);
    }
#line 1779 "Parser.cpp"
    break;

  case 84: // call_expression: declaration_ref_expression "(" parameter_list ")"
#line 445 "rvlang.yy"
                                                      {
      // auto* declRef = compiler.getAstContext()->newNode<rvlang::DeclRefExpr>(compiler.location(), $1, nullptr);
      yylhs.value.as < rvlang::Expr* > () = compiler.getAstContext()->newNode<rvlang::CallExpr>(compiler.location(), yystack_[3].value.as < rvlang::DeclRefExpr* > (), std::move(yystack_[1].value.as < std::vector<rvlang::Expr*> > ()));
    }
#line 1788 "Parser.cpp"
    break;

  case 85: // call_expression: declaration_ref_expression "(" ")"
#line 449 "rvlang.yy"
                                       {
      // auto* declRef = compiler.getAstContext()->newNode<rvlang::DeclRefExpr>(compiler.location(), $1, nullptr);
      yylhs.value.as < rvlang::Expr* > () = compiler.getAstContext()->newNode<rvlang::CallExpr>(compiler.location(), yystack_[2].value.as < rvlang::DeclRefExpr* > ());
    }
#line 1797 "Parser.cpp"
    break;

  case 86: // parameter_list: parameter
#line 456 "rvlang.yy"
              {
      yylhs.value.as < std::vector<rvlang::Expr*> > () = std::vector<rvlang::Expr*>();
      yylhs.value.as < std::vector<rvlang::Expr*> > ().push_back(yystack_[0].value.as < rvlang::Expr* > ());
    }
#line 1806 "Parser.cpp"
    break;

  case 87: // parameter_list: parameter_list "," parameter
#line 460 "rvlang.yy"
                                 {
      yystack_[2].value.as < std::vector<rvlang::Expr*> > ().push_back(yystack_[0].value.as < rvlang::Expr* > ());
      yylhs.value.as < std::vector<rvlang::Expr*> > () = std::move(yystack_[2].value.as < std::vector<rvlang::Expr*> > ());
    }
#line 1815 "Parser.cpp"
    break;

  case 88: // parameter: expression
#line 466 "rvlang.yy"
                      { yylhs.value.as < rvlang::Expr* > () = yystack_[0].value.as < rvlang::Expr* > (); }
#line 1821 "Parser.cpp"
    break;

  case 89: // selection_statement: "if" "(" expression ")" compound_statement
#line 470 "rvlang.yy"
                                               {
      yylhs.value.as < rvlang::Stmt* > () = compiler.getAstContext()->newNode<rvlang::IfStmt>(compiler.location(), yystack_[2].value.as < rvlang::Expr* > (), yystack_[0].value.as < rvlang::CompoundStmt* > ());
    }
#line 1829 "Parser.cpp"
    break;

  case 90: // selection_statement: "if" "(" expression ")" compound_statement "else" compound_statement
#line 473 "rvlang.yy"
                                                                         {
      yylhs.value.as < rvlang::Stmt* > () = compiler.getAstContext()->newNode<rvlang::IfStmt>(compiler.location(), yystack_[4].value.as < rvlang::Expr* > (), yystack_[2].value.as < rvlang::CompoundStmt* > (), yystack_[0].value.as < rvlang::CompoundStmt* > ());
    }
#line 1837 "Parser.cpp"
    break;

  case 91: // iteration_statement: "while" "(" expression ")" compound_statement
#line 479 "rvlang.yy"
                                                  {
      yylhs.value.as < rvlang::Stmt* > () = compiler.getAstContext()->newNode<rvlang::WhileStmt>(compiler.location(), yystack_[2].value.as < rvlang::Expr* > (), yystack_[0].value.as < rvlang::CompoundStmt* > ());
    }
#line 1845 "Parser.cpp"
    break;

  case 92: // jump_statement: "continue" ";"
#line 486 "rvlang.yy"
                   {
      yylhs.value.as < rvlang::Stmt* > () = compiler.getAstContext()->newNode<rvlang::ContinueStmt>(compiler.location());
    }
#line 1853 "Parser.cpp"
    break;

  case 93: // jump_statement: "break" ";"
#line 489 "rvlang.yy"
                {
      yylhs.value.as < rvlang::Stmt* > () = compiler.getAstContext()->newNode<rvlang::BreakStmt>(compiler.location());
    }
#line 1861 "Parser.cpp"
    break;

  case 94: // jump_statement: "return" expression ";"
#line 492 "rvlang.yy"
                            {
      yylhs.value.as < rvlang::Stmt* > () = compiler.getAstContext()->newNode<rvlang::ReturnStmt>(compiler.location(), yystack_[1].value.as < rvlang::Expr* > ());
    }
#line 1869 "Parser.cpp"
    break;


#line 1873 "Parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      yy_lac_discard_ ("error recovery");
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    static const char *const yy_sname[] =
    {
    "end of file", "error", "invalid token", "=", "-", "+", "*", "/", "(",
  ")", "{", "}", "[", "]", "==", "!=", ">", "<", ">=", "<=", "&&", "||",
  "!", "%", "<<", ">>", "~", "&", "|", "^", "void", "char", "short", "int",
  "signed", "unsigned", "float", "if", "else", "for", "while", ";", ",",
  "continue", "break", "return", "struct", "IDENTIFIER", "STRING_LITERAL",
  "CONSTANT", "long", "$accept", "translation_unit", "declaration_list",
  "declaration", "function_declaration", "array_declaration", "elements",
  "delaration_specifiers", "pointer", "type_specifier",
  "parameter_decl_list", "parameter_declaration", "compound_statement",
  "statement_list", "declaration_or_statement", "declare_statement",
  "variable_declaration", "expression", "declaration_ref_expression",
  "array_subscript_expression", "unary_expression",
  "dereference_expression", "binary_expression", "binary_operator",
  "statement", "expression_statement", "assignment_expression",
  "call_expression", "parameter_list", "parameter", "selection_statement",
  "iteration_statement", "jump_statement", YY_NULLPTR
    };
    return yy_sname[yysymbol];
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

#if YYDEBUG
    // Execute LAC once. We don't care if it is successful, we
    // only do it for the sake of debugging output.
    if (!yyparser_.yy_lac_established_)
      yyparser_.yy_lac_check_ (yyla_.kind ());
#endif

    for (int yyx = 0; yyx < YYNTOKENS; ++yyx)
      {
        symbol_kind_type yysym = YY_CAST (symbol_kind_type, yyx);
        if (yysym != symbol_kind::S_YYerror
            && yysym != symbol_kind::S_YYUNDEF
            && yyparser_.yy_lac_check_ (yysym))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = yysym;
          }
      }
    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }




  bool
  parser::yy_lac_check_ (symbol_kind_type yytoken) const
  {
    // Logically, the yylac_stack's lifetime is confined to this function.
    // Clear it, to get rid of potential left-overs from previous call.
    yylac_stack_.clear ();
    // Reduce until we encounter a shift and thereby accept the token.
#if YYDEBUG
    YYCDEBUG << "LAC: checking lookahead " << symbol_name (yytoken) << ':';
#endif
    std::ptrdiff_t lac_top = 0;
    while (true)
      {
        state_type top_state = (yylac_stack_.empty ()
                                ? yystack_[lac_top].state
                                : yylac_stack_.back ());
        int yyrule = yypact_[+top_state];
        if (yy_pact_value_is_default_ (yyrule)
            || (yyrule += yytoken) < 0 || yylast_ < yyrule
            || yycheck_[yyrule] != yytoken)
          {
            // Use the default action.
            yyrule = yydefact_[+top_state];
            if (yyrule == 0)
              {
                YYCDEBUG << " Err\n";
                return false;
              }
          }
        else
          {
            // Use the action from yytable.
            yyrule = yytable_[yyrule];
            if (yy_table_value_is_error_ (yyrule))
              {
                YYCDEBUG << " Err\n";
                return false;
              }
            if (0 < yyrule)
              {
                YYCDEBUG << " S" << yyrule << '\n';
                return true;
              }
            yyrule = -yyrule;
          }
        // By now we know we have to simulate a reduce.
        YYCDEBUG << " R" << yyrule - 1;
        // Pop the corresponding number of values from the stack.
        {
          std::ptrdiff_t yylen = yyr2_[yyrule];
          // First pop from the LAC stack as many tokens as possible.
          std::ptrdiff_t lac_size = std::ptrdiff_t (yylac_stack_.size ());
          if (yylen < lac_size)
            {
              yylac_stack_.resize (std::size_t (lac_size - yylen));
              yylen = 0;
            }
          else if (lac_size)
            {
              yylac_stack_.clear ();
              yylen -= lac_size;
            }
          // Only afterwards look at the main stack.
          // We simulate popping elements by incrementing lac_top.
          lac_top += yylen;
        }
        // Keep top_state in sync with the updated stack.
        top_state = (yylac_stack_.empty ()
                     ? yystack_[lac_top].state
                     : yylac_stack_.back ());
        // Push the resulting state of the reduction.
        state_type state = yy_lr_goto_state_ (top_state, yyr1_[yyrule]);
        YYCDEBUG << " G" << int (state);
        yylac_stack_.push_back (state);
      }
  }

  // Establish the initial context if no initial context currently exists.
  bool
  parser::yy_lac_establish_ (symbol_kind_type yytoken)
  {
    /* Establish the initial context for the current lookahead if no initial
       context is currently established.

       We define a context as a snapshot of the parser stacks.  We define
       the initial context for a lookahead as the context in which the
       parser initially examines that lookahead in order to select a
       syntactic action.  Thus, if the lookahead eventually proves
       syntactically unacceptable (possibly in a later context reached via a
       series of reductions), the initial context can be used to determine
       the exact set of tokens that would be syntactically acceptable in the
       lookahead's place.  Moreover, it is the context after which any
       further semantic actions would be erroneous because they would be
       determined by a syntactically unacceptable token.

       yy_lac_establish_ should be invoked when a reduction is about to be
       performed in an inconsistent state (which, for the purposes of LAC,
       includes consistent states that don't know they're consistent because
       their default reductions have been disabled).

       For parse.lac=full, the implementation of yy_lac_establish_ is as
       follows.  If no initial context is currently established for the
       current lookahead, then check if that lookahead can eventually be
       shifted if syntactic actions continue from the current context.  */
    if (yy_lac_established_)
      return true;
    else
      {
#if YYDEBUG
        YYCDEBUG << "LAC: initial context established for "
                 << symbol_name (yytoken) << '\n';
#endif
        yy_lac_established_ = true;
        return yy_lac_check_ (yytoken);
      }
  }

  // Discard any previous initial lookahead context.
  void
  parser::yy_lac_discard_ (const char* event)
  {
   /* Discard any previous initial lookahead context because of Event,
      which may be a lookahead change or an invalidation of the currently
      established initial context for the current lookahead.

      The most common example of a lookahead change is a shift.  An example
      of both cases is syntax error recovery.  That is, a syntax error
      occurs when the lookahead is syntactically erroneous for the
      currently established initial context, so error recovery manipulates
      the parser stacks to try to find a new initial context in which the
      current lookahead is syntactically acceptable.  If it fails to find
      such a context, it discards the lookahead.  */
    if (yy_lac_established_)
      {
        YYCDEBUG << "LAC: initial context discarded due to "
                 << event << '\n';
        yy_lac_established_ = false;
      }
  }


  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
         In the first two cases, it might appear that the current syntax
         error should have been detected in the previous state when
         yy_lac_check was invoked.  However, at that time, there might
         have been a different syntax error that discarded a different
         initial context during error recovery, leaving behind the
         current lookahead.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -58;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
      33,   -58,   -58,   -58,   -58,    66,   -58,   -58,    47,    33,
     -58,   -58,   -58,   -36,     6,    45,   -58,   -58,   -58,   -58,
     -58,   -58,   -58,    26,   -58,   -58,    27,    33,    31,   -58,
      27,    -5,    27,    27,    27,   -58,   -58,   -58,   150,    12,
     -58,   -58,   -58,   -58,   -58,    35,    14,   -58,    78,   404,
      84,   262,   392,   392,   392,   -58,   -58,   -58,   -58,   -58,
     -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,
     -58,   -58,   -58,   -58,    27,    10,    27,   -58,     0,    33,
      -1,    27,   -58,   366,   -58,   366,    30,   -58,   288,    75,
     -58,   -58,   -58,    90,   -58,   -58,   -58,    27,   -58,   -58,
      93,    94,    72,    76,    27,    74,   103,   -58,   -58,   -58,
      86,   120,   -58,   -58,   -58,    83,   -58,   -58,   -58,    77,
     -58,    27,    27,   -58,   -58,   178,    11,   -58,   -58,    27,
      27,   -58,   -58,     4,   314,   340,   -58,   206,   234,    87,
      80,   117,   117,   -58,   -58,   -58,   -58,    92,   -58,   117,
     -58
  };

  const signed char
  parser::yydefact_[] =
  {
       0,    18,    19,    20,    21,     0,    23,    22,     0,     2,
       3,     5,     7,     0,    15,    14,     6,    24,    25,    26,
      27,     1,     4,     0,    17,    16,     0,    28,     0,    39,
       0,     0,     0,     0,     0,    50,    42,    41,     0,    43,
      49,    44,    55,    45,    46,     0,     0,    29,     0,    56,
       0,     0,    52,    53,    54,    59,    58,    60,    61,    65,
      66,    69,    70,    67,    68,    71,    72,    62,    63,    64,
      73,    74,    75,    40,     0,     0,     0,    31,     0,     0,
       0,     0,    47,    57,    85,    88,     0,    86,     0,     0,
       8,     9,    30,     0,    10,    48,    84,     0,    51,    33,
       0,     0,     0,     0,     0,     0,     0,    34,    37,    38,
       0,     0,    36,    76,    80,     0,    77,    78,    79,     0,
      87,     0,     0,    92,    93,     0,     0,    32,    35,     0,
       0,    81,    12,     0,     0,     0,    94,     0,     0,     0,
       0,     0,     0,    83,    82,    11,    13,    89,    91,     0,
      90
  };

  const signed char
  parser::yypgoto_[] =
  {
     -58,   -58,   -58,   122,   -58,   -58,   -58,   -18,   -58,   -58,
     -58,    53,   -57,   -58,    36,   -58,   -29,   -26,   -27,   -58,
     -58,   -19,   -58,   -58,   -58,   -58,   -58,   -16,   -58,    40,
     -58,   -58,   -58
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     8,     9,    10,    11,    12,   133,    13,    14,    15,
      46,    47,    91,   106,   107,   108,    16,    85,    39,    40,
      41,    42,    43,    74,   112,   113,   114,    44,    86,    87,
     116,   117,   118
  };

  const unsigned char
  parser::yytable_[] =
  {
      38,    30,    93,    31,    49,    51,    52,    53,    54,    45,
      89,    23,    24,    50,    26,   139,    30,    32,    31,    84,
      75,    33,    34,    78,    76,     1,     2,     3,     4,    26,
       5,     6,    32,    30,    27,    31,    33,    34,    28,    96,
      94,    90,    35,    36,    37,     7,   140,    21,    83,    32,
      88,    25,    29,    33,    34,    95,    79,    35,    36,    37,
     109,    45,   110,     1,     2,     3,     4,    29,     5,     6,
     111,   105,    97,   115,    35,    36,    37,   109,   125,   110,
      48,    30,    77,     7,   147,   148,    99,   111,   105,   129,
     115,    80,   150,    81,    75,   134,   135,    17,    18,    19,
     119,   121,   122,   137,   138,     1,     2,     3,     4,    30,
       5,     6,   100,   123,   127,   101,    20,   124,   102,   103,
     104,   126,    35,   130,   131,     7,   132,    89,   145,   146,
     149,    22,    92,     1,     2,     3,     4,   120,     5,     6,
     100,     0,   128,   101,     0,     0,   102,   103,   104,     0,
      35,     0,     0,     7,    55,    56,    57,    58,     0,     0,
       0,     0,     0,     0,    59,    60,    61,    62,    63,    64,
      65,    66,     0,    67,    68,    69,     0,    70,    71,    72,
       0,     0,    55,    56,    57,    58,     0,     0,     0,     0,
       0,    73,    59,    60,    61,    62,    63,    64,    65,    66,
       0,    67,    68,    69,     0,    70,    71,    72,     0,     0,
      55,    56,    57,    58,     0,     0,     0,     0,     0,   136,
      59,    60,    61,    62,    63,    64,    65,    66,     0,    67,
      68,    69,     0,    70,    71,    72,     0,     0,    55,    56,
      57,    58,     0,     0,     0,     0,     0,   143,    59,    60,
      61,    62,    63,    64,    65,    66,     0,    67,    68,    69,
       0,    70,    71,    72,     0,     0,    55,    56,    57,    58,
       0,    82,     0,     0,     0,   144,    59,    60,    61,    62,
      63,    64,    65,    66,     0,    67,    68,    69,     0,    70,
      71,    72,    55,    56,    57,    58,     0,     0,     0,     0,
       0,    98,    59,    60,    61,    62,    63,    64,    65,    66,
       0,    67,    68,    69,     0,    70,    71,    72,    55,    56,
      57,    58,     0,   141,     0,     0,     0,     0,    59,    60,
      61,    62,    63,    64,    65,    66,     0,    67,    68,    69,
       0,    70,    71,    72,    55,    56,    57,    58,     0,   142,
       0,     0,     0,     0,    59,    60,    61,    62,    63,    64,
      65,    66,     0,    67,    68,    69,     0,    70,    71,    72,
      55,    56,    57,    58,     0,     0,     0,     0,     0,     0,
      59,    60,    61,    62,    63,    64,    65,    66,     0,    67,
      68,    69,     0,    70,    71,    72,    55,    56,    57,    58,
       0,     0,     0,     0,     0,     0,    59,    60,    61,    62,
      63,    64,     0,     0,     0,    67,    68,    69,    59,    60,
      61,    62,    63,    64,     0,     0,     0,    67,    68,    69
  };

  const short
  parser::yycheck_[] =
  {
      26,     6,     3,     8,    30,    31,    32,    33,    34,    27,
      10,    47,     6,    31,     3,    11,     6,    22,     8,     9,
       8,    26,    27,     9,    12,    30,    31,    32,    33,     3,
      35,    36,    22,     6,     8,     8,    26,    27,    12,     9,
      41,    41,    47,    48,    49,    50,    42,     0,    74,    22,
      76,     6,    41,    26,    27,    81,    42,    47,    48,    49,
      89,    79,    89,    30,    31,    32,    33,    41,    35,    36,
      89,    89,    42,    89,    47,    48,    49,   106,   104,   106,
      49,     6,    47,    50,   141,   142,    11,   106,   106,     3,
     106,    13,   149,     9,     8,   121,   122,    31,    32,    33,
      10,     8,     8,   129,   130,    30,    31,    32,    33,     6,
      35,    36,    37,    41,    11,    40,    50,    41,    43,    44,
      45,    47,    47,     3,    41,    50,    49,    10,    41,    49,
      38,     9,    79,    30,    31,    32,    33,    97,    35,    36,
      37,    -1,   106,    40,    -1,    -1,    43,    44,    45,    -1,
      47,    -1,    -1,    50,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    -1,    -1,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    23,    24,    25,    -1,    27,    28,    29,
      -1,    -1,     4,     5,     6,     7,    -1,    -1,    -1,    -1,
      -1,    41,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    23,    24,    25,    -1,    27,    28,    29,    -1,    -1,
       4,     5,     6,     7,    -1,    -1,    -1,    -1,    -1,    41,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,    23,
      24,    25,    -1,    27,    28,    29,    -1,    -1,     4,     5,
       6,     7,    -1,    -1,    -1,    -1,    -1,    41,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    23,    24,    25,
      -1,    27,    28,    29,    -1,    -1,     4,     5,     6,     7,
      -1,     9,    -1,    -1,    -1,    41,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    23,    24,    25,    -1,    27,
      28,    29,     4,     5,     6,     7,    -1,    -1,    -1,    -1,
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    23,    24,    25,    -1,    27,    28,    29,     4,     5,
       6,     7,    -1,     9,    -1,    -1,    -1,    -1,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    23,    24,    25,
      -1,    27,    28,    29,     4,     5,     6,     7,    -1,     9,
      -1,    -1,    -1,    -1,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    23,    24,    25,    -1,    27,    28,    29,
       4,     5,     6,     7,    -1,    -1,    -1,    -1,    -1,    -1,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,    23,
      24,    25,    -1,    27,    28,    29,     4,     5,     6,     7,
      -1,    -1,    -1,    -1,    -1,    -1,    14,    15,    16,    17,
      18,    19,    -1,    -1,    -1,    23,    24,    25,    14,    15,
      16,    17,    18,    19,    -1,    -1,    -1,    23,    24,    25
  };

  const signed char
  parser::yystos_[] =
  {
       0,    30,    31,    32,    33,    35,    36,    50,    52,    53,
      54,    55,    56,    58,    59,    60,    67,    31,    32,    33,
      50,     0,    54,    47,     6,     6,     3,     8,    12,    41,
       6,     8,    22,    26,    27,    47,    48,    49,    68,    69,
      70,    71,    72,    73,    78,    58,    61,    62,    49,    68,
      58,    68,    68,    68,    68,     4,     5,     6,     7,    14,
      15,    16,    17,    18,    19,    20,    21,    23,    24,    25,
      27,    28,    29,    41,    74,     8,    12,    47,     9,    42,
      13,     9,     9,    68,     9,    68,    79,    80,    68,    10,
      41,    63,    62,     3,    41,    68,     9,    42,    13,    11,
      37,    40,    43,    44,    45,    58,    64,    65,    66,    67,
      69,    72,    75,    76,    77,    78,    81,    82,    83,    10,
      80,     8,     8,    41,    41,    68,    47,    11,    65,     3,
       3,    41,    49,    57,    68,    68,    41,    68,    68,    11,
      42,     9,     9,    41,    41,    41,    49,    63,    63,    38,
      63
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    51,    52,    53,    53,    54,    54,    54,    55,    55,
      56,    56,    57,    57,    58,    58,    59,    59,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    61,    61,
      61,    62,    63,    63,    64,    64,    65,    65,    66,    67,
      67,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      69,    70,    71,    71,    71,    71,    72,    73,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    75,    75,    75,    75,
      76,    76,    77,    77,    78,    78,    79,    79,    80,    81,
      81,    82,    83,    83,    83
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     1,     1,     1,     6,     6,
       6,    10,     1,     3,     1,     1,     2,     2,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     2,     0,     1,
       3,     2,     3,     2,     1,     2,     1,     1,     1,     3,
       5,     1,     1,     1,     1,     1,     1,     3,     4,     1,
       1,     4,     2,     2,     2,     1,     2,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     4,     4,     4,     3,     1,     3,     1,     5,
       7,     5,     2,     2,     3
  };




#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   154,   154,   162,   166,   172,   173,   174,   178,   181,
     187,   195,   209,   213,   221,   222,   226,   234,   245,   248,
     251,   254,   257,   260,   263,   266,   269,   272,   278,   279,
     283,   290,   296,   299,   303,   307,   314,   315,   318,   322,
     325,   331,   338,   349,   350,   351,   352,   353,   354,   357,
     361,   367,   373,   376,   377,   380,   384,   388,   394,   395,
     396,   397,   398,   399,   400,   401,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   415,   416,   417,   418,
     421,   422,   426,   431,   445,   449,   456,   460,   466,   470,
     473,   479,   486,   489,   492
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 2600 "Parser.cpp"

#line 510 "rvlang.yy"


void yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
