#include <algorithm>
#include "TableCellParser.h"
#include "./StringUtils.cpp"
#include "TokenValues.cpp"

TableCell TableCellParser::parse(const std::string &string) const {
    if (_isInteger(string)) {
        return TableCell(CellType::INTEGER, string);
    } else if (_isDecimal(string)) {
        return TableCell(CellType::DECIMAL, string);
    } else if (_isFormula(string)) {
        return TableCell(CellType::FORMULA, string);
    } else {
        return TableCell(CellType::STRING, string);
    }
}

bool TableCellParser::_isFormula(const std::string &string) const {
    return false;
}

bool TableCellParser::_isInteger(const std::string &s) const {
    std::string trimmed = s;
    trim(trimmed);

    for (char c : trimmed) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool TableCellParser::_isDecimal(const std::string &s) const {
    std::string trimmed = s;
    trim(trimmed);

    std::string decimalSeparator = TOKEN_VALUES[TokenType::DECIMAL_SEPARATOR];
    bool foundDecimalSeparator = false;
    for (char c : trimmed) {
        if (std::isdigit(c)) {
            continue;
        } else if (std::string(1, c) == decimalSeparator) {
            if (foundDecimalSeparator) {
                return false;
            }
            foundDecimalSeparator = true;
        } else {
            return false;
        }
    }
    return !s.empty();
}
