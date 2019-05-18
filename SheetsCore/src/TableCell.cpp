#include <TableCell.h>

TableCell::TableCell() : _type(CellType::STRING), _value("") {
}

TableCell::TableCell(CellType type, std::string value) : _type(type), _value(std::move(value)) {
}

std::string TableCell::getValue() const {
    return _value;
}

CellType TableCell::getType() const {
    return _type;
}
