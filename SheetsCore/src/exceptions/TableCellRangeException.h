#pragma once


#include <stdexcept>

namespace SheetsCore {

    class TableCellRangeException : public std::invalid_argument {
    public:
        TableCellRangeException();
    };

}


