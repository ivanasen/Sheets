#include <utility>

#include "TableCell.h"

namespace SheetsCore {
    TableCell::TableCell() : _value(""), _type(CellType::STRING) {
    }

    TableCell::TableCell(CellType type, std::string value)
            : _type(type), _value(std::move(value)) {
    }

    std::string TableCell::getValue() {
        return _value;
    }

    CellType TableCell::getType() const {
        return _type;
    }

    TableCell::TableCell(const TableCell &tableCell)
            : _type(tableCell._type), _value(tableCell._value) {
    }
}

