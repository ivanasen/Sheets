#include <iomanip>
#include <Strings.h>
#include "DecimalTableCell.h"

namespace core {

    DecimalTableCell::DecimalTableCell(double value)
            : _value(value), _strValue(std::to_string(value)) {
        _formatValue();
    }

    std::string DecimalTableCell::getValue() {
        return _strValue;
    }

    double DecimalTableCell::getDecimalValue() const {
        return _value;
    }

    CellType DecimalTableCell::getType() const {
        return CellType::DECIMAL;
    }

    std::string DecimalTableCell::getDisplayValue() {
        return _formattedValue;
    }

    DecimalTableCell::~DecimalTableCell() = default;

    void DecimalTableCell::_formatValue() {
        _formattedValue = utils::Strings::formatAsDisplayDecimalValue(_value);
    }

    TableCell *DecimalTableCell::clone() {
        auto *newCell = new DecimalTableCell(_value);
        return newCell;
    }
}