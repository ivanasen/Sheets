#include <iostream>
#include "IntegerTableCell.h"

IntegerTableCell::IntegerTableCell(int value) {
    _value = value;
}

std::string IntegerTableCell::getValue() {
    return std::to_string(_value);
}

void IntegerTableCell::setValue(std::string const &value) {
    _value = std::stoi(value);
}
