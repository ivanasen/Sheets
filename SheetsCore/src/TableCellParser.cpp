#include <algorithm>
#include "TableCellParser.h"
#include "./StringUtils.cpp"

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

    bool foundDecimalSeparator = false;
    for (char c : trimmed) {
        if (std::isdigit(c)) {
            continue;
        } else if (c == '.') {
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
