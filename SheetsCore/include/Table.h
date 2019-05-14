#pragma once

#include <vector>
#include <string>
#include "TableCell.h"

class Table {
public:
    const TableCell &getCell(unsigned row, unsigned col) const;

    void setCellValue(const std::string &value);

private:
    std::vector<std::vector<TableCell>> _tableValues;
};
