#pragma once

#include "TableCell.h"

namespace SheetsCore {

    class TableCellParser {
    public:
        static TableCell parse(size_t row, size_t col, const std::string &string);
    };

}


