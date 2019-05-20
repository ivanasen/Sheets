#pragma once

#include "TokenType.h"
#include "Token.h"

namespace SheetsCore {
    //This should have been a map, but we can't use them, so....
    //Everywhere we use this now w=e need to cast TokenType to int, since we're using strict enums
    static std::vector<Token> TOKEN_VALUES{
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
    };
}