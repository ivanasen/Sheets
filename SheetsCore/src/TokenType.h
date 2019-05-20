#pragma once

namespace SheetsCore {

    //Order of these shouldn't be changed, since TokenValues array depends on it
    enum class TokenType : int {
        DECIMAL_SEPARATOR,
        COMMA,
        OPENING_PARENTHESIS,
        CLOSING_PARENTHESIS,
        PLUS,
        MINUS,
        MULTIPLICATION,
        DIVISION,
        EQUAL,
        ROW,
        COLUMN,
        IDENTIFIER,
        STRING,
        NUMBER
    };

}