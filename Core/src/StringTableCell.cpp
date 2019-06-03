#include <Strings.h>
#include "StringTableCell.h"

namespace core {

    core::StringTableCell::StringTableCell(std::string value)
            : _value(std::move(value)) {
        _escapedValue = utils::Strings::addQuotes(utils::Strings::escape(_value));
    }

    std::string core::StringTableCell::getDisplayValue() {
        return _value;
    }

    std::string core::StringTableCell::getValue() {
        return _escapedValue;
    }

    core::CellType core::StringTableCell::getType() const {
        return CellType::STRING;
    }

    TableCell *StringTableCell::clone() {
        auto *newCell = new StringTableCell(_value);
        return newCell;
    }

    core::StringTableCell::~StringTableCell() = default;
}