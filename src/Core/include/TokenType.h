#pragma once

namespace core {

    //Adding custom int type for enum, since TOKEN_VALUES isn't a map anymore, and we'll need to do casts everywhere
    enum class TokenType : int {
        DECIMAL_SEPARATOR = 0,
        COMMA = 1,
        OPENING_PARENTHESIS = 2,
        CLOSING_PARENTHESIS = 3,
        PLUS = 4,
        MINUS = 5,
        MULTIPLICATION = 6,
        DIVISION = 7,
        EQUAL = 8,
        ROW = 9,
        COLUMN = 10,
        ROW_SEPARATOR = 11,
        COLUMN_SEPARATOR = 12,
        STRING_SEPARATOR = 13,
        ESCAPE_CHARACTER = 14,
        IDENTIFIER = 15,
        STRING = 16,
        NUMBER = 17,
        TABLE_CELL = 18
    };

}