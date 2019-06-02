#include "IntegerTableCell.h"

namespace core {

    IntegerTableCell::IntegerTableCell(int value)
            : _value(value), _strValue(std::to_string(value)) {
    }

    std::string IntegerTableCell::getDisplayValue() {
        return _strValue;
    }

    std::string IntegerTableCell::getValue() {
        return _strValue;
    }

    CellType IntegerTableCell::getType() const {
        return CellType::INTEGER;
    }

    int IntegerTableCell::getIntValue() const {
        return _value;
    }

    IntegerTableCell::~IntegerTableCell() = default;

}