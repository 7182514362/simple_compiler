#include "Token.h"

namespace rvlang {
bool isBinaryBoolToken(Token tok) {
  return tok == Token::EQ || tok == Token::NEQ || tok == Token::GT ||
         tok == Token::LT || tok == Token::GE || tok == Token::LE ||
         tok == Token::LOGIC_AND || tok == Token::LOGIC_OR;
};

bool isUnaryBoolToken(Token tok) { return tok == Token::LOGIC_NOT; }

#define TOKEN_ENTRY(token, name) (name)

std::array<std::string_view, static_cast<int>(Token::TOKEN_END)>
    g_tokenNameList = {
        TOKEN_ENTRY(ASSIGN, "="),
        TOKEN_ENTRY(PLUS, "+"),
        TOKEN_ENTRY(MINUS, "-"),
        TOKEN_ENTRY(STAR, "*"),
        TOKEN_ENTRY(SLASH, "/"),
        TOKEN_ENTRY(LPAREN, "("),
        TOKEN_ENTRY(RPAREN, ")"),
        TOKEN_ENTRY(LBRACE, "{"),
        TOKEN_ENTRY(RBRACE, "}"),

        TOKEN_ENTRY(LBRACKET, "["),
        TOKEN_ENTRY(RBRACKET, "]"),

        TOKEN_ENTRY(EQ, "=="),
        TOKEN_ENTRY(NEQ, "!="),
        TOKEN_ENTRY(GT, ">"),
        TOKEN_ENTRY(LT, "<"),
        TOKEN_ENTRY(GE, ">="),
        TOKEN_ENTRY(LE, "<="),
        TOKEN_ENTRY(LOGIC_AND, "&&"),
        TOKEN_ENTRY(LOGIC_OR, "||"),
        TOKEN_ENTRY(LOGIC_NOT, "!"),

        TOKEN_ENTRY(PERCENT, "%"),
        TOKEN_ENTRY(LSHIFT, "<<"),
        TOKEN_ENTRY(RSHIFT, ">>"),

        TOKEN_ENTRY(NOT, "~"),
        TOKEN_ENTRY(AND, "&"),
        TOKEN_ENTRY(OR, "|"),
        TOKEN_ENTRY(XOR, "^"),

        TOKEN_ENTRY(VOID, "void"),
        TOKEN_ENTRY(CHAR, "char"),
        TOKEN_ENTRY(SHORT, "short"),
        TOKEN_ENTRY(INT, "int"),

        TOKEN_ENTRY(SIGNED, "signed"),
        TOKEN_ENTRY(UNSIGNED, "unsigned"),

        TOKEN_ENTRY(IF, "if"),
        TOKEN_ENTRY(ELSE, "else"),
        TOKEN_ENTRY(FOR, "for"),
        TOKEN_ENTRY(WHILE, "while"),

        TOKEN_ENTRY(SEMICOLON, ";"),
        TOKEN_ENTRY(COMMA, ","),
        TOKEN_ENTRY(CONTINUE, "continue"),
        TOKEN_ENTRY(BREAK, "break"),
        TOKEN_ENTRY(RETURN, "return"),
        TOKEN_ENTRY(STRUCT, "struct"),
};
} // namespace rvlang