#pragma once


#include <stdexcept>

class UnknownElementException : public std::invalid_argument {
public:
    UnknownElementException(size_t tableRow, size_t tableCol, const std::string &value);
};


