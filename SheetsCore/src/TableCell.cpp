#include <utility>

#include "TableCell.h"

namespace SheetsCore {
    TableCell::TableCell() : _tablePosition(0, 0), _value(""), _type(CellType::STRING) {
    }

    TableCell::TableCell(size_t row, size_t column, CellType type, std::string value)
            : _tablePosition(row, column), _type(type), _value(std::move(value)) {
    }

    std::string TableCell::getValue() {
        return _value;
    }

    CellType TableCell::getType() const {
        return _type;
    }

    TableCell::TableCell(const TableCell &tableCell)
            : _tablePosition(tableCell._tablePosition), _type(tableCell._type), _value(tableCell._value) {
    }

    TableCellPosition TableCell::getTablePosition() const {
        return _tablePosition;
    }
}

