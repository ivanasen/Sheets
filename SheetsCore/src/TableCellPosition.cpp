#include "TableCellPosition.h"

TableCellPosition::TableCellPosition(size_t row, size_t column) : row(row), column(column) {
}

bool TableCellPosition::operator==(const TableCellPosition &other) const {
    return row == other.row && column == other.column;
}
