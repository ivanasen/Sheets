#include <algorithm>
#include "TableCellParser.h"
#include "./StringUtils.cpp"
#include "TokenValues.h"
#include "ArithmeticFormulasUtils.h"

namespace SheetsCore {

    TableCell TableCellParser::parse(const std::string &string) {
        if (isInteger(string)) {
            return TableCell(CellType::INTEGER, string);
        } else if (isDecimal(string)) {
            return TableCell(CellType::DECIMAL, string);
        } else if (ArithmeticFormulasUtils::isFormula(string)) {
            return TableCell(CellType::FORMULA, string);
        } else {
            return TableCell(CellType::STRING, string);
        }
    }
}
