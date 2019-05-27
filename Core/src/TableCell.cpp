#include <utility>

#include "TableCell.h"

namespace core {
    TableCell::TableCell() : _value(""), _type(CellType::STRING) {
    }

    TableCell::TableCell(CellType type, std::string value)
            : _type(type), _value(std::move(value)) {
    }

    TableCell::TableCell(const TableCell &tableCell)
            : _type(tableCell._type), _value(tableCell._value) {
    }

    std::string TableCell::getValue() {
        return _value;
    }

    CellType TableCell::getType() const {
        return _type;
    }
}

