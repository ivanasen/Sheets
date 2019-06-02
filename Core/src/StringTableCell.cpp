#include <Strings.h>
#include "StringTableCell.h"

namespace core {

    core::StringTableCell::StringTableCell(const std::string &value) {
        _value = utils::Strings::unescape(value);
        _escapedValue = utils::Strings::addQuotes(utils::Strings::escape(value));
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

    core::StringTableCell::~StringTableCell() = default;
}