#pragma once

#include "TableCell.h"

namespace SheetsCore {

    class TableCellParser {
    public:
        static TableCell parse(const std::string &string);
    };

}


