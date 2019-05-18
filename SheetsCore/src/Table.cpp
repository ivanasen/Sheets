#include "Table.h"

TableCell Table::getCell(unsigned row, unsigned col) const {
    if (row > _tableValues.size() - 1 || col > _tableValues.size() - 1) {
        return TableCell(CellType::STRING, std::string());
    }
    return _tableValues[row][col];
}

Table::Table(unsigned initialHeight, unsigned initialWidth)
        : _tableValues(initialHeight, std::vector<TableCell>(initialWidth)) {
}

void Table::setCellValue(unsigned row, unsigned col, const std::string &cellValue) {
    _resizeIfNeeded(row + 1, col + 1);

    TableCell newCell = _cellParser.parse(cellValue);

    if (newCell.getType() == CellType::FORMULA) {
        //....
    } else {
        _tableValues[row][col] = newCell;
    }
}

void Table::_resizeIfNeeded(unsigned requiredHeight, unsigned requiredWidth) {
    if (requiredHeight > _tableValues.size()) {
        _tableValues.resize(requiredHeight);
    }

    if ((_tableValues.empty() && requiredWidth > 0) || requiredWidth > _tableValues[0].size()) {
        for (std::vector<TableCell> &row : _tableValues) {
            row.resize(requiredWidth);
        }
    }
}
