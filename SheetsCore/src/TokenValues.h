#pragma once

#include <unordered_map>
#include "TokenType.h"
#include "Token.h"

namespace SheetsCore {

    static std::unordered_map<TokenType, Token> TOKEN_VALUES{
            {TokenType::COMMA,               Token(TokenType::COMMA, ",")},
            {TokenType::OPENING_PARENTHESIS, Token(TokenType::OPENING_PARENTHESIS, "(")},
            {TokenType::CLOSING_PARENTHESIS, Token(TokenType::CLOSING_PARENTHESIS, ")")},
            {TokenType::PLUS,                Token(TokenType::PLUS, "+")},
            {TokenType::MINUS,               Token(TokenType::MINUS, "-")},
            {TokenType::MULTIPLICATION,      Token(TokenType::MULTIPLICATION, "*")},
            {TokenType::DIVISION,            Token(TokenType::DIVISION, "/")},
            {TokenType::EQUAL,               Token(TokenType::EQUAL, "=")},
            {TokenType::DECIMAL_SEPARATOR,   Token(TokenType::DECIMAL_SEPARATOR, ".")},
            {TokenType::ROW,                 Token(TokenType::ROW, "R")},
            {TokenType::COLUMN,              Token(TokenType::COLUMN, "C")},
    };
}