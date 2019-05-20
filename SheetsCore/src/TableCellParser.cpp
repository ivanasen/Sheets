#include <algorithm>
#include "TableCellParser.h"
#include "./StringUtils.h"
#include "TokenValues.h"
#include "ArithmeticFormulasUtils.h"

namespace SheetsCore {

    TableCell TableCellParser::parse(size_t row, size_t col, const std::string &string) {
        if (StringUtils::isInteger(string)) {
            return TableCell(row, col, CellType::INTEGER, string);
        } else if (StringUtils::isDecimal(string)) {
            return TableCell(row, col, CellType::DECIMAL, string);
        } else if (ArithmeticFormulasUtils::isFormula(string)) {
            return TableCell(row, col, CellType::FORMULA, string);
        } else {
            return TableCell(row, col, CellType::STRING, string);
        }
    }
}
