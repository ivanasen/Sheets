#include "UnknownElementException.h"

UnknownElementException::UnknownElementException(size_t tableRow, size_t tableCol, const std::string &value)
        : invalid_argument("Error: Row " + std::to_string(tableRow)
                           + ", Col " + std::to_string(tableCol)
                           + ", " + value + " is an unknown data type.") {
}
