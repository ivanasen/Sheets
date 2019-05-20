#include <cctype>
#include <stdexcept>
#include "TableCellPosition.h"
#include "StringUtils.h"
#include "ArithmeticFormulasUtils.h"
#include "TokenValues.h"

namespace SheetsCore {

    TableCellPosition::TableCellPosition(size_t row, size_t column)
            : _row(row), _column(column) {
    }

    bool TableCellPosition::operator==(const TableCellPosition &other) const {
        return _row == other.getRow() && _column == other.getColumn();
    }

    TableCellPosition::TableCellPosition(std::string identifier) {
        StringUtils::trim(identifier);

        if (!ArithmeticFormulasUtils::isTableCellIdentifier(identifier)) {
            throw std::invalid_argument("Invalid table cell identifier: \"" + identifier + "\"");
        }

        std::string rowToken = TOKEN_VALUES[TokenType::ROW].value;
        std::string colToken = TOKEN_VALUES[TokenType::COLUMN].value;

        std::string rowStr;
        std::string colStr;

        std::string::iterator iterator = identifier.begin() + rowToken.size();

        while (iterator < identifier.end() && std::isdigit(*iterator)) {
            rowStr += *(iterator++);
        }
        iterator += colToken.size();
        while (iterator < identifier.end() && std::isdigit(*iterator)) {
            colStr += *(iterator++);
        }

        _row = std::stoul(rowStr) - 1;
        _column = std::stoul(colStr) - 1;
    }

    size_t TableCellPosition::getRow() const {
        return _row;
    }

    size_t TableCellPosition::getColumn() const {
        return _column;
    }
}