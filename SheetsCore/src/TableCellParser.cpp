#include <algorithm>
#include "TableCellParser.h"
#include "./StringUtils.h"
#include "TokenValues.h"
#include "ArithmeticFormulasUtils.h"

namespace SheetsCore {

    TableCell TableCellParser::parse(const std::string &string) {
        if (StringUtils::isInteger(string)) {
            return TableCell(CellType::INTEGER, string);
        } else if (StringUtils::isDecimal(string)) {
            return TableCell(CellType::DECIMAL, string);
        } else if (ArithmeticFormulasUtils::isFormula(string)) {
            return TableCell(CellType::FORMULA, string);
        } else {
            return TableCell(CellType::STRING, string);
        }
    }
}
