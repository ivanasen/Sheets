#include <regex>
#include "TokenValues.h"

namespace SheetsCore {
    static const std::regex TABLE_CELL_FORMAT(
            "^"
            + TOKEN_VALUES[(int) TokenType::ROW].value +
            "[0-9]+"
            + TOKEN_VALUES[(int) TokenType::COLUMN].value +
            "[0-9]+$");

    static const std::string ERROR_TABLE_CELL_VALUE = "ERROR";
}
