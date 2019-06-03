#pragma once

#include "Token.h"

namespace core {
    //This should have been a map, but we can't use them, so....
    //Everywhere we use this now we need to cast TokenType to int, since we're using strict enums
    const std::vector<Token> TOKEN_VALUES{
            Token(TokenType::DECIMAL_SEPARATOR, "."),
            Token(TokenType::COMMA, ","),
            Token(TokenType::OPENING_PARENTHESIS, "("),
            Token(TokenType::CLOSING_PARENTHESIS, ")"),
            Token(TokenType::PLUS, "+"),
            Token(TokenType::MINUS, "-"),
            Token(TokenType::MULTIPLICATION, "*"),
            Token(TokenType::DIVISION, "/"),
            Token(TokenType::EQUAL, "="),
            Token(TokenType::ROW, "R"),
            Token(TokenType::COLUMN, "C"),
            Token(TokenType::ROW_SEPARATOR, "\n"),
            Token(TokenType::COLUMN_SEPARATOR, ","),
            Token(TokenType::STRING_SEPARATOR, "\""),
            Token(TokenType::ESCAPE_CHARACTER, "\\")
    };
}