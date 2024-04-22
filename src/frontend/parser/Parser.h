// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file Parser.h
 ** Define the yy::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
// "%code requires" blocks.
#line 11 "rvlang.yy"

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

#line 64 "Parser.h"

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "location.hh"
#include <typeinfo>
#ifndef YY_ASSERT
# include <cassert>
# define YY_ASSERT assert
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

namespace yy {
#line 204 "Parser.h"




  /// A Bison parser.
  class parser
  {
  public:
#ifdef YYSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define YYSTYPE in C++, use %define api.value.type"
# endif
    typedef YYSTYPE value_type;
#else
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class value_type
  {
  public:
    /// Type of *this.
    typedef value_type self_type;

    /// Empty construction.
    value_type () YY_NOEXCEPT
      : yyraw_ ()
      , yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    value_type (YY_RVREF (T) t)
      : yytypeid_ (&typeid (T))
    {
      YY_ASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    value_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~value_type () YY_NOEXCEPT
    {
      YY_ASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == *that.yytypeid_);
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    value_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yyraw_;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yyraw_;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // delaration_specifiers
      // pointer
      // type_specifier
      char dummy1[sizeof (const rvlang::Type*)];

      // CONSTANT
      char dummy2[sizeof (int)];

      // compound_statement
      char dummy3[sizeof (rvlang::CompoundStmt*)];

      // translation_unit
      // declaration
      // function_declaration
      // array_declaration
      // variable_declaration
      char dummy4[sizeof (rvlang::Decl*)];

      // declaration_ref_expression
      char dummy5[sizeof (rvlang::DeclRefExpr*)];

      // expression
      // array_subscript_expression
      // unary_expression
      // dereference_expression
      // binary_expression
      // assignment_expression
      // call_expression
      // parameter
      char dummy6[sizeof (rvlang::Expr*)];

      // parameter_declaration
      char dummy7[sizeof (rvlang::ParamDecl*)];

      // declaration_or_statement
      // declare_statement
      // statement
      // expression_statement
      // selection_statement
      // iteration_statement
      // jump_statement
      char dummy8[sizeof (rvlang::Stmt*)];

      // "="
      // "-"
      // "+"
      // "*"
      // "/"
      // "("
      // ")"
      // "{"
      // "}"
      // "["
      // "]"
      // "=="
      // "!="
      // ">"
      // "<"
      // ">="
      // "<="
      // "&&"
      // "||"
      // "!"
      // "%"
      // "<<"
      // ">>"
      // "~"
      // "&"
      // "|"
      // "^"
      // "void"
      // "char"
      // "short"
      // "int"
      // "signed"
      // "unsigned"
      // "float"
      // "if"
      // "else"
      // "for"
      // "while"
      // ";"
      // ","
      // "continue"
      // "break"
      // "return"
      // "struct"
      // binary_operator
      char dummy9[sizeof (rvlang::Token)];

      // IDENTIFIER
      // STRING_LITERAL
      char dummy10[sizeof (std::string)];

      // elements
      char dummy11[sizeof (std::vector<int>)];

      // declaration_list
      char dummy12[sizeof (std::vector<rvlang::Decl*>)];

      // parameter_list
      char dummy13[sizeof (std::vector<rvlang::Expr*>)];

      // parameter_decl_list
      char dummy14[sizeof (std::vector<rvlang::ParamDecl*>)];

      // statement_list
      char dummy15[sizeof (std::vector<rvlang::Stmt*>)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me_;
      /// A buffer large enough to store any of the semantic values.
      char yyraw_[size];
    };

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };

#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;

    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        TOK_YYEMPTY = -2,
    TOK_YYEOF = 0,                 // "end of file"
    TOK_YYerror = 1,               // error
    TOK_YYUNDEF = 2,               // "invalid token"
    TOK_ASSIGN = 3,                // "="
    TOK_MINUS = 4,                 // "-"
    TOK_PLUS = 5,                  // "+"
    TOK_STAR = 6,                  // "*"
    TOK_SLASH = 7,                 // "/"
    TOK_LPAREN = 8,                // "("
    TOK_RPAREN = 9,                // ")"
    TOK_LBRACE = 10,               // "{"
    TOK_RBRACE = 11,               // "}"
    TOK_LBRACKET = 12,             // "["
    TOK_RBRACKET = 13,             // "]"
    TOK_EQ = 14,                   // "=="
    TOK_NEQ = 15,                  // "!="
    TOK_GT = 16,                   // ">"
    TOK_LT = 17,                   // "<"
    TOK_GE = 18,                   // ">="
    TOK_LE = 19,                   // "<="
    TOK_LOGIC_AND = 20,            // "&&"
    TOK_LOGIC_OR = 21,             // "||"
    TOK_LOGIC_NOT = 22,            // "!"
    TOK_PERCENT = 23,              // "%"
    TOK_LSHIFT = 24,               // "<<"
    TOK_RSHIFT = 25,               // ">>"
    TOK_NOT = 26,                  // "~"
    TOK_AND = 27,                  // "&"
    TOK_OR = 28,                   // "|"
    TOK_XOR = 29,                  // "^"
    TOK_VOID = 30,                 // "void"
    TOK_CHAR = 31,                 // "char"
    TOK_SHORT = 32,                // "short"
    TOK_INT = 33,                  // "int"
    TOK_SIGNED = 34,               // "signed"
    TOK_UNSIGNED = 35,             // "unsigned"
    TOK_FLOAT = 36,                // "float"
    TOK_IF = 37,                   // "if"
    TOK_ELSE = 38,                 // "else"
    TOK_FOR = 39,                  // "for"
    TOK_WHILE = 40,                // "while"
    TOK_SEMICOLON = 41,            // ";"
    TOK_COMMA = 42,                // ","
    TOK_CONTINUE = 43,             // "continue"
    TOK_BREAK = 44,                // "break"
    TOK_RETURN = 45,               // "return"
    TOK_STRUCT = 46,               // "struct"
    TOK_IDENTIFIER = 47,           // IDENTIFIER
    TOK_STRING_LITERAL = 48,       // STRING_LITERAL
    TOK_CONSTANT = 49              // CONSTANT
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 51, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_ASSIGN = 3,                            // "="
        S_MINUS = 4,                             // "-"
        S_PLUS = 5,                              // "+"
        S_STAR = 6,                              // "*"
        S_SLASH = 7,                             // "/"
        S_LPAREN = 8,                            // "("
        S_RPAREN = 9,                            // ")"
        S_LBRACE = 10,                           // "{"
        S_RBRACE = 11,                           // "}"
        S_LBRACKET = 12,                         // "["
        S_RBRACKET = 13,                         // "]"
        S_EQ = 14,                               // "=="
        S_NEQ = 15,                              // "!="
        S_GT = 16,                               // ">"
        S_LT = 17,                               // "<"
        S_GE = 18,                               // ">="
        S_LE = 19,                               // "<="
        S_LOGIC_AND = 20,                        // "&&"
        S_LOGIC_OR = 21,                         // "||"
        S_LOGIC_NOT = 22,                        // "!"
        S_PERCENT = 23,                          // "%"
        S_LSHIFT = 24,                           // "<<"
        S_RSHIFT = 25,                           // ">>"
        S_NOT = 26,                              // "~"
        S_AND = 27,                              // "&"
        S_OR = 28,                               // "|"
        S_XOR = 29,                              // "^"
        S_VOID = 30,                             // "void"
        S_CHAR = 31,                             // "char"
        S_SHORT = 32,                            // "short"
        S_INT = 33,                              // "int"
        S_SIGNED = 34,                           // "signed"
        S_UNSIGNED = 35,                         // "unsigned"
        S_FLOAT = 36,                            // "float"
        S_IF = 37,                               // "if"
        S_ELSE = 38,                             // "else"
        S_FOR = 39,                              // "for"
        S_WHILE = 40,                            // "while"
        S_SEMICOLON = 41,                        // ";"
        S_COMMA = 42,                            // ","
        S_CONTINUE = 43,                         // "continue"
        S_BREAK = 44,                            // "break"
        S_RETURN = 45,                           // "return"
        S_STRUCT = 46,                           // "struct"
        S_IDENTIFIER = 47,                       // IDENTIFIER
        S_STRING_LITERAL = 48,                   // STRING_LITERAL
        S_CONSTANT = 49,                         // CONSTANT
        S_50_long_ = 50,                         // "long"
        S_YYACCEPT = 51,                         // $accept
        S_translation_unit = 52,                 // translation_unit
        S_declaration_list = 53,                 // declaration_list
        S_declaration = 54,                      // declaration
        S_function_declaration = 55,             // function_declaration
        S_array_declaration = 56,                // array_declaration
        S_elements = 57,                         // elements
        S_delaration_specifiers = 58,            // delaration_specifiers
        S_pointer = 59,                          // pointer
        S_type_specifier = 60,                   // type_specifier
        S_parameter_decl_list = 61,              // parameter_decl_list
        S_parameter_declaration = 62,            // parameter_declaration
        S_compound_statement = 63,               // compound_statement
        S_statement_list = 64,                   // statement_list
        S_declaration_or_statement = 65,         // declaration_or_statement
        S_declare_statement = 66,                // declare_statement
        S_variable_declaration = 67,             // variable_declaration
        S_expression = 68,                       // expression
        S_declaration_ref_expression = 69,       // declaration_ref_expression
        S_array_subscript_expression = 70,       // array_subscript_expression
        S_unary_expression = 71,                 // unary_expression
        S_dereference_expression = 72,           // dereference_expression
        S_binary_expression = 73,                // binary_expression
        S_binary_operator = 74,                  // binary_operator
        S_statement = 75,                        // statement
        S_expression_statement = 76,             // expression_statement
        S_assignment_expression = 77,            // assignment_expression
        S_call_expression = 78,                  // call_expression
        S_parameter_list = 79,                   // parameter_list
        S_parameter = 80,                        // parameter
        S_selection_statement = 81,              // selection_statement
        S_iteration_statement = 82,              // iteration_statement
        S_jump_statement = 83                    // jump_statement
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol () YY_NOEXCEPT
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
        , location (std::move (that.location))
      {
        switch (this->kind ())
    {
      case symbol_kind::S_delaration_specifiers: // delaration_specifiers
      case symbol_kind::S_pointer: // pointer
      case symbol_kind::S_type_specifier: // type_specifier
        value.move< const rvlang::Type* > (std::move (that.value));
        break;

      case symbol_kind::S_CONSTANT: // CONSTANT
        value.move< int > (std::move (that.value));
        break;

      case symbol_kind::S_compound_statement: // compound_statement
        value.move< rvlang::CompoundStmt* > (std::move (that.value));
        break;

      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_declaration: // declaration
      case symbol_kind::S_function_declaration: // function_declaration
      case symbol_kind::S_array_declaration: // array_declaration
      case symbol_kind::S_variable_declaration: // variable_declaration
        value.move< rvlang::Decl* > (std::move (that.value));
        break;

      case symbol_kind::S_declaration_ref_expression: // declaration_ref_expression
        value.move< rvlang::DeclRefExpr* > (std::move (that.value));
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_array_subscript_expression: // array_subscript_expression
      case symbol_kind::S_unary_expression: // unary_expression
      case symbol_kind::S_dereference_expression: // dereference_expression
      case symbol_kind::S_binary_expression: // binary_expression
      case symbol_kind::S_assignment_expression: // assignment_expression
      case symbol_kind::S_call_expression: // call_expression
      case symbol_kind::S_parameter: // parameter
        value.move< rvlang::Expr* > (std::move (that.value));
        break;

      case symbol_kind::S_parameter_declaration: // parameter_declaration
        value.move< rvlang::ParamDecl* > (std::move (that.value));
        break;

      case symbol_kind::S_declaration_or_statement: // declaration_or_statement
      case symbol_kind::S_declare_statement: // declare_statement
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_expression_statement: // expression_statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_iteration_statement: // iteration_statement
      case symbol_kind::S_jump_statement: // jump_statement
        value.move< rvlang::Stmt* > (std::move (that.value));
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
        value.move< rvlang::Token > (std::move (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
        value.move< std::string > (std::move (that.value));
        break;

      case symbol_kind::S_elements: // elements
        value.move< std::vector<int> > (std::move (that.value));
        break;

      case symbol_kind::S_declaration_list: // declaration_list
        value.move< std::vector<rvlang::Decl*> > (std::move (that.value));
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        value.move< std::vector<rvlang::Expr*> > (std::move (that.value));
        break;

      case symbol_kind::S_parameter_decl_list: // parameter_decl_list
        value.move< std::vector<rvlang::ParamDecl*> > (std::move (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.move< std::vector<rvlang::Stmt*> > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, const rvlang::Type*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const const rvlang::Type*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, int&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const int& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, rvlang::CompoundStmt*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const rvlang::CompoundStmt*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, rvlang::Decl*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const rvlang::Decl*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, rvlang::DeclRefExpr*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const rvlang::DeclRefExpr*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, rvlang::Expr*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const rvlang::Expr*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, rvlang::ParamDecl*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const rvlang::ParamDecl*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, rvlang::Stmt*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const rvlang::Stmt*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, rvlang::Token&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const rvlang::Token& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<int>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<int>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<rvlang::Decl*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<rvlang::Decl*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<rvlang::Expr*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<rvlang::Expr*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<rvlang::ParamDecl*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<rvlang::ParamDecl*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<rvlang::Stmt*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<rvlang::Stmt*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }



      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_delaration_specifiers: // delaration_specifiers
      case symbol_kind::S_pointer: // pointer
      case symbol_kind::S_type_specifier: // type_specifier
        value.template destroy< const rvlang::Type* > ();
        break;

      case symbol_kind::S_CONSTANT: // CONSTANT
        value.template destroy< int > ();
        break;

      case symbol_kind::S_compound_statement: // compound_statement
        value.template destroy< rvlang::CompoundStmt* > ();
        break;

      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_declaration: // declaration
      case symbol_kind::S_function_declaration: // function_declaration
      case symbol_kind::S_array_declaration: // array_declaration
      case symbol_kind::S_variable_declaration: // variable_declaration
        value.template destroy< rvlang::Decl* > ();
        break;

      case symbol_kind::S_declaration_ref_expression: // declaration_ref_expression
        value.template destroy< rvlang::DeclRefExpr* > ();
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_array_subscript_expression: // array_subscript_expression
      case symbol_kind::S_unary_expression: // unary_expression
      case symbol_kind::S_dereference_expression: // dereference_expression
      case symbol_kind::S_binary_expression: // binary_expression
      case symbol_kind::S_assignment_expression: // assignment_expression
      case symbol_kind::S_call_expression: // call_expression
      case symbol_kind::S_parameter: // parameter
        value.template destroy< rvlang::Expr* > ();
        break;

      case symbol_kind::S_parameter_declaration: // parameter_declaration
        value.template destroy< rvlang::ParamDecl* > ();
        break;

      case symbol_kind::S_declaration_or_statement: // declaration_or_statement
      case symbol_kind::S_declare_statement: // declare_statement
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_expression_statement: // expression_statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_iteration_statement: // iteration_statement
      case symbol_kind::S_jump_statement: // jump_statement
        value.template destroy< rvlang::Stmt* > ();
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
        value.template destroy< rvlang::Token > ();
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
        value.template destroy< std::string > ();
        break;

      case symbol_kind::S_elements: // elements
        value.template destroy< std::vector<int> > ();
        break;

      case symbol_kind::S_declaration_list: // declaration_list
        value.template destroy< std::vector<rvlang::Decl*> > ();
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        value.template destroy< std::vector<rvlang::Expr*> > ();
        break;

      case symbol_kind::S_parameter_decl_list: // parameter_decl_list
        value.template destroy< std::vector<rvlang::ParamDecl*> > ();
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.template destroy< std::vector<rvlang::Stmt*> > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      const char *name () const YY_NOEXCEPT
      {
        return parser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Default constructor.
      by_kind () YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) YY_NOEXCEPT;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that) YY_NOEXCEPT;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t) YY_NOEXCEPT;



      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () YY_NOEXCEPT {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type (token_kind_type (tok), std::move (l))
#else
      symbol_type (int tok, const location_type& l)
        : super_type (token_kind_type (tok), l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == token::TOK_YYEOF
                   || (token::TOK_YYerror <= tok && tok <= token::TOK_YYUNDEF)
                   || tok == 305);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, int v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const int& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == token::TOK_CONSTANT);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, rvlang::Token v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const rvlang::Token& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT ((token::TOK_ASSIGN <= tok && tok <= token::TOK_STRUCT));
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT ((token::TOK_IDENTIFIER <= tok && tok <= token::TOK_STRING_LITERAL));
#endif
      }
    };

    /// Build a parser object.
    parser (rvlang::CompilerInstance& compiler_yyarg);
    virtual ~parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    parser (const parser&) = delete;
    /// Non copyable.
    parser& operator= (const parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static const char *symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each token kind.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYEOF (location_type l)
      {
        return symbol_type (token::TOK_YYEOF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYEOF (const location_type& l)
      {
        return symbol_type (token::TOK_YYEOF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror (location_type l)
      {
        return symbol_type (token::TOK_YYerror, std::move (l));
      }
#else
      static
      symbol_type
      make_YYerror (const location_type& l)
      {
        return symbol_type (token::TOK_YYerror, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF (location_type l)
      {
        return symbol_type (token::TOK_YYUNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYUNDEF (const location_type& l)
      {
        return symbol_type (token::TOK_YYUNDEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_ASSIGN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ASSIGN (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_ASSIGN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MINUS (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_MINUS, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_MINUS (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_MINUS, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PLUS (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_PLUS, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PLUS (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_PLUS, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STAR (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_STAR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_STAR (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_STAR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SLASH (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_SLASH, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SLASH (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_SLASH, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LPAREN (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_LPAREN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LPAREN (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_LPAREN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RPAREN (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_RPAREN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RPAREN (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_RPAREN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LBRACE (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_LBRACE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LBRACE (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_LBRACE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RBRACE (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_RBRACE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RBRACE (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_RBRACE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LBRACKET (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_LBRACKET, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LBRACKET (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_LBRACKET, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RBRACKET (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_RBRACKET, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RBRACKET (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_RBRACKET, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQ (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_EQ, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_EQ (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_EQ, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NEQ (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_NEQ, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_NEQ (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_NEQ, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GT (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_GT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_GT (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_GT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LT (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_LT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LT (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_LT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GE (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_GE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_GE (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_GE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LE (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_LE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LE (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_LE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LOGIC_AND (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_LOGIC_AND, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LOGIC_AND (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_LOGIC_AND, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LOGIC_OR (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_LOGIC_OR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LOGIC_OR (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_LOGIC_OR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LOGIC_NOT (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_LOGIC_NOT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LOGIC_NOT (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_LOGIC_NOT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PERCENT (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_PERCENT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PERCENT (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_PERCENT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LSHIFT (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_LSHIFT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LSHIFT (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_LSHIFT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RSHIFT (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_RSHIFT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RSHIFT (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_RSHIFT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NOT (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_NOT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_NOT (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_NOT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AND (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_AND, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_AND (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_AND, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OR (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_OR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_OR (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_OR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_XOR (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_XOR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_XOR (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_XOR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VOID (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_VOID, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_VOID (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_VOID, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CHAR (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_CHAR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CHAR (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_CHAR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SHORT (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_SHORT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SHORT (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_SHORT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INT (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_INT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_INT (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_INT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SIGNED (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_SIGNED, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SIGNED (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_SIGNED, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNSIGNED (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_UNSIGNED, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_UNSIGNED (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_UNSIGNED, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLOAT (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_FLOAT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_FLOAT (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_FLOAT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IF (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_IF, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IF (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_IF, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELSE (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_ELSE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ELSE (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_ELSE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FOR (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_FOR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_FOR (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_FOR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WHILE (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_WHILE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_WHILE (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_WHILE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SEMICOLON (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_SEMICOLON, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SEMICOLON (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_SEMICOLON, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMA (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_COMMA, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_COMMA (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_COMMA, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONTINUE (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_CONTINUE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CONTINUE (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_CONTINUE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BREAK (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_BREAK, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_BREAK (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_BREAK, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RETURN (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_RETURN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RETURN (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_RETURN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRUCT (rvlang::Token v, location_type l)
      {
        return symbol_type (token::TOK_STRUCT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_STRUCT (const rvlang::Token& v, const location_type& l)
      {
        return symbol_type (token::TOK_STRUCT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IDENTIFIER (std::string v, location_type l)
      {
        return symbol_type (token::TOK_IDENTIFIER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IDENTIFIER (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_IDENTIFIER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRING_LITERAL (std::string v, location_type l)
      {
        return symbol_type (token::TOK_STRING_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_STRING_LITERAL (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_STRING_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONSTANT (int v, location_type l)
      {
        return symbol_type (token::TOK_CONSTANT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CONSTANT (const int& v, const location_type& l)
      {
        return symbol_type (token::TOK_CONSTANT, v, l);
      }
#endif


    class context
    {
    public:
      context (const parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    parser (const parser&);
    /// Non copyable.
    parser& operator= (const parser&);
#endif

    /// Check the lookahead yytoken.
    /// \returns  true iff the token will be eventually shifted.
    bool yy_lac_check_ (symbol_kind_type yytoken) const;
    /// Establish the initial context if no initial context currently exists.
    /// \returns  true iff the token will be eventually shifted.
    bool yy_lac_establish_ (symbol_kind_type yytoken);
    /// Discard any previous initial lookahead context because of event.
    /// \param event  the event which caused the lookahead to be discarded.
    ///               Only used for debbuging output.
    void yy_lac_discard_ (const char* event);

    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT;

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;



    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const signed char yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const unsigned char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const unsigned char yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const signed char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200) YY_NOEXCEPT
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range) YY_NOEXCEPT
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;
    /// The stack for LAC.
    /// Logically, the yy_lac_stack's lifetime is confined to the function
    /// yy_lac_check_. We just store it as a member of this class to hold
    /// on to the memory and to avoid frequent reallocations.
    /// Since yy_lac_check_ is const, this member must be mutable.
    mutable std::vector<state_type> yylac_stack_;
    /// Whether an initial LAC context was established.
    bool yy_lac_established_;


    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum
    {
      yylast_ = 429,     ///< Last index in yytable_.
      yynnts_ = 33,  ///< Number of nonterminal symbols.
      yyfinal_ = 21 ///< Termination state number.
    };


    // User arguments.
    rvlang::CompilerInstance& compiler;

  };

  inline
  parser::symbol_kind_type
  parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    return static_cast<symbol_kind_type> (t);
  }

  // basic_symbol.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_delaration_specifiers: // delaration_specifiers
      case symbol_kind::S_pointer: // pointer
      case symbol_kind::S_type_specifier: // type_specifier
        value.copy< const rvlang::Type* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CONSTANT: // CONSTANT
        value.copy< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_compound_statement: // compound_statement
        value.copy< rvlang::CompoundStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_declaration: // declaration
      case symbol_kind::S_function_declaration: // function_declaration
      case symbol_kind::S_array_declaration: // array_declaration
      case symbol_kind::S_variable_declaration: // variable_declaration
        value.copy< rvlang::Decl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration_ref_expression: // declaration_ref_expression
        value.copy< rvlang::DeclRefExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_array_subscript_expression: // array_subscript_expression
      case symbol_kind::S_unary_expression: // unary_expression
      case symbol_kind::S_dereference_expression: // dereference_expression
      case symbol_kind::S_binary_expression: // binary_expression
      case symbol_kind::S_assignment_expression: // assignment_expression
      case symbol_kind::S_call_expression: // call_expression
      case symbol_kind::S_parameter: // parameter
        value.copy< rvlang::Expr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameter_declaration: // parameter_declaration
        value.copy< rvlang::ParamDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration_or_statement: // declaration_or_statement
      case symbol_kind::S_declare_statement: // declare_statement
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_expression_statement: // expression_statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_iteration_statement: // iteration_statement
      case symbol_kind::S_jump_statement: // jump_statement
        value.copy< rvlang::Stmt* > (YY_MOVE (that.value));
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
        value.copy< rvlang::Token > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_elements: // elements
        value.copy< std::vector<int> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration_list: // declaration_list
        value.copy< std::vector<rvlang::Decl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        value.copy< std::vector<rvlang::Expr*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameter_decl_list: // parameter_decl_list
        value.copy< std::vector<rvlang::ParamDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.copy< std::vector<rvlang::Stmt*> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  parser::symbol_kind_type
  parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_delaration_specifiers: // delaration_specifiers
      case symbol_kind::S_pointer: // pointer
      case symbol_kind::S_type_specifier: // type_specifier
        value.move< const rvlang::Type* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_CONSTANT: // CONSTANT
        value.move< int > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_compound_statement: // compound_statement
        value.move< rvlang::CompoundStmt* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_declaration: // declaration
      case symbol_kind::S_function_declaration: // function_declaration
      case symbol_kind::S_array_declaration: // array_declaration
      case symbol_kind::S_variable_declaration: // variable_declaration
        value.move< rvlang::Decl* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_declaration_ref_expression: // declaration_ref_expression
        value.move< rvlang::DeclRefExpr* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_array_subscript_expression: // array_subscript_expression
      case symbol_kind::S_unary_expression: // unary_expression
      case symbol_kind::S_dereference_expression: // dereference_expression
      case symbol_kind::S_binary_expression: // binary_expression
      case symbol_kind::S_assignment_expression: // assignment_expression
      case symbol_kind::S_call_expression: // call_expression
      case symbol_kind::S_parameter: // parameter
        value.move< rvlang::Expr* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_parameter_declaration: // parameter_declaration
        value.move< rvlang::ParamDecl* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_declaration_or_statement: // declaration_or_statement
      case symbol_kind::S_declare_statement: // declare_statement
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_expression_statement: // expression_statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_iteration_statement: // iteration_statement
      case symbol_kind::S_jump_statement: // jump_statement
        value.move< rvlang::Stmt* > (YY_MOVE (s.value));
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
        value.move< rvlang::Token > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
        value.move< std::string > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_elements: // elements
        value.move< std::vector<int> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_declaration_list: // declaration_list
        value.move< std::vector<rvlang::Decl*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        value.move< std::vector<rvlang::Expr*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_parameter_decl_list: // parameter_decl_list
        value.move< std::vector<rvlang::ParamDecl*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.move< std::vector<rvlang::Stmt*> > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  inline
  parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  inline
  parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  inline
  void
  parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  parser::symbol_kind_type
  parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  inline
  parser::symbol_kind_type
  parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


} // yy
#line 2925 "Parser.h"




#endif // !YY_YY_PARSER_H_INCLUDED
