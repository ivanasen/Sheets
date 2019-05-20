#pragma once

namespace SheetsCore {

    enum class TokenType {
        DECIMAL_SEPARATOR,
        COMMA,
        OPENING_PARENTHESIS,
        CLOSING_PARENTHESIS,
        PLUS,
        MINUS,
        MULTIPLICATION,
        DIVISION,
        IDENTIFIER,
        STRING,
        NUMBER,
        EQUAL,
        ROW,
        COLUMN
    };

}