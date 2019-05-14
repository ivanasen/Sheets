#include "Table.h"

const TableCell &Table::getCell(unsigned row, unsigned col) const {
    return *_tableValues[row][col];
}

std::string Table::getCellValue(unsigned row, unsigned col) const {
    return _tableValues[row][col]->getValue();
}

void Table::setCellValue(unsigned row, unsigned col, const std::string &value) {
//    try {
//        _tableValues[row][col]->setValue(value);
//    } catch

}