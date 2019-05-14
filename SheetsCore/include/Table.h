#pragma once

#include <vector>
#include <string>
#include <memory>
#include "TableCell.h"

class Table {
public:
    const TableCell &getCell(unsigned row, unsigned col) const;

    std::string getCellValue(unsigned row, unsigned col) const;

    void setCellValue(unsigned row, unsigned col, const std::string &value);

private:
    std::vector<std::vector<std::shared_ptr<TableCell>>> _tableValues;
};
