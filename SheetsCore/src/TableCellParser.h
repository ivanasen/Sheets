#pragma once

#include <TableCell.h>
#include <string>
#include <bits/shared_ptr.h>

class TableCellParser {
public:
    TableCell parse(const std::string &cellValue) const;
};


