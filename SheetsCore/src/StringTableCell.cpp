#include <utility>

#include <utility>

#include "StringTableCell.h"

StringTableCell::StringTableCell(std::string value) : _value(std::move(value)) {
}

std::string StringTableCell::getValue() {
    return _value;
}

void StringTableCell::setValue(const std::string &value) {
    _value = value;
}
