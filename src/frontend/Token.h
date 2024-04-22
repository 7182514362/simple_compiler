#pragma once
#include <array>
#include <string>

namespace rvlang {
enum class Token {
  ASSIGN, // "="
  PLUS,   // "+"
  MINUS,  // "-"
  STAR,   // "*"
  SLASH,  // "/"
  LPAREN, // "("
  RPAREN, // ")"
  LBRACE, // "{"
  RBRACE, // "}"

  LBRACKET, // "["
  RBRACKET, // "]"

  EQ,        // "=="
  NEQ,       // "!="
  GT,        // ">"
  LT,        // "<"
  GE,        // ">="
  LE,        // "<="
  LOGIC_AND, // "&&"
  LOGIC_OR,  // "||"
  LOGIC_NOT, // "!"

  PERCENT, // "%"
  LSHIFT,  // "<<"
  RSHIFT,  // ">>"

  NOT, // "~"
  AND, // "&"
  OR,  // "|"
  XOR, // "^"

  VOID,  // "void"
  CHAR,  // "char"
  SHORT, // "short"
  INT,   // "int"

  SIGNED,   // "signed"
  UNSIGNED, // "unsigned"

  IF,    // "if"
  ELSE,  // "else"
  FOR,   // "for"
  WHILE, // "while"

  SEMICOLON, // ";"
  COMMA,     // ","
  CONTINUE,  // "continue"
  BREAK,     // "break"
  RETURN,    // "return"
  STRUCT,    // "struct"

  TOKEN_END
};

extern std::array<std::string_view, static_cast<int>(Token::TOKEN_END)>
    g_tokenNameList;

bool isBinaryBoolToken(Token tok);
bool isUnaryBoolToken(Token tok);

inline const std::string_view getTokenName(Token tok) {
  return g_tokenNameList[static_cast<int>(tok)];
}
} // namespace rvlang