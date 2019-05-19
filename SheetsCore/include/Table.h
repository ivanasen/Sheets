#pragma once

#include <vector>
#include <string>
#include <memory>
#include "TableCell.h"
#include "../src/TableCellParser.h"

class Table {
public:
    Table(unsigned initialHeight, unsigned initialWidth);

    std::string getCellValue(unsigned row, unsigned col) const;

    void setCellValue(unsigned row, unsigned col, const std::string &cellValue);

private:
    std::vector<std::vector<TableCell>> _tableValues;

    void _resizeIfNeeded(unsigned requiredHeight, unsigned requiredWidth);
};
