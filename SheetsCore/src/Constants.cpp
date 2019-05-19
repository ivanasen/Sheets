#pragma once

#include <regex>
#include "TokenValues.h"

namespace SheetsCore {
    static std::regex TABLE_CELL_FORMAT(
            "^"
            + TOKEN_VALUES[TokenType::ROW].value +
            "[0-9]+"
            + TOKEN_VALUES[TokenType::COLUMN].value +
            "[0-9]+$");
}
