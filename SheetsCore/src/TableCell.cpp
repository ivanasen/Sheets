#include <utility>

#include "TableCell.h"

TableCell::TableCell() : _value(""), _type(CellType::STRING) {
}

TableCell::TableCell(CellType type, std::string value) : _type(type), _value(std::move(value)) {

}

std::string TableCell::getValue() const {
    return _value;
}

CellType TableCell::getType() const {
    return _type;
}
