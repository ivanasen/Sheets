#include "DoubleTableCell.h"

DoubleTableCell::DoubleTableCell(double value) {
    _value = value;
}

std::string DoubleTableCell::getValue() {
    return std::to_string(_value);
}

void DoubleTableCell::setValue(const std::string &value) {
    _value = std::stod(value);
}
