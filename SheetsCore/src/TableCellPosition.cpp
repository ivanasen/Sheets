#include <cctype>
#include <stdexcept>
#include <Table.h>
#include "TableCellPosition.h"
#include <Strings.h>
#include <regex>
#include "ArithmeticFormulasUtils.h"
#include "TokenValues.h"
#include "exceptions/TableCellRangeException.h"

namespace SheetsCore {

    const std::regex TableCellPosition::TABLE_CELL_FORMAT(
            "^"
            + TOKEN_VALUES[(int) TokenType::ROW].value +
            "[0-9]+"
            + TOKEN_VALUES[(int) TokenType::COLUMN].value +
            "[0-9]+$");

    TableCellPosition::TableCellPosition(size_t row, size_t column)
            : _row(row), _column(column) {
    }

    bool TableCellPosition::operator==(const TableCellPosition &other) const {
        return _row == other.getRow() && _column == other.getColumn();
    }

    TableCellPosition::TableCellPosition(std::string identifier) {
        Utils::Strings::trim(identifier);

        if (!isTableCellIdentifier(identifier)) {
            throw std::invalid_argument("Invalid table cell identifier: \"" + identifier + "\"");
        }

        std::string rowToken = TOKEN_VALUES[(int) TokenType::ROW].value;
        std::string colToken = TOKEN_VALUES[(int) TokenType::COLUMN].value;

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

        try {

            long row = std::stoul(rowStr) - 1;
            long column = std::stoul(colStr) - 1;

            if (row < 0 || column < 0 || row > Table::MAX_SIZE || column > Table::MAX_SIZE) {
                throw TableCellRangeException();
            }

            _row = row;
            _column = column;

        } catch (const std::out_of_range &e) {
            throw TableCellRangeException();
        }
    }

    size_t TableCellPosition::getRow() const {
        return _row;
    }

    size_t TableCellPosition::getColumn() const {
        return _column;
    }

    bool TableCellPosition::isTableCellIdentifier(const std::string &s) {
        return std::regex_match(s, TABLE_CELL_FORMAT);
    }
}