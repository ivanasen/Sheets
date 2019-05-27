#pragma once


#include <stdexcept>

namespace core {

    class TableCellRangeException : public std::invalid_argument {
    public:
        TableCellRangeException();
    };

}


