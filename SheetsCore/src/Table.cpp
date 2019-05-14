#include "Table.h"

const TableCell &Table::getCell(unsigned row, unsigned col) const {
    return _tableValues[row][col];
}

void Table::setCellValue(const std::string &value) {

}
