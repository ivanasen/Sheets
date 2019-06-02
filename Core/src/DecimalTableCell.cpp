#include <iomanip>
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
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << _value;
        _formattedValue = stream.str();
    }
}