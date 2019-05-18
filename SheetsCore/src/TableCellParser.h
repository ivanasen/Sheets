#pragma once


#include "TableCell.h"

class TableCellParser {
public:
    TableCell parse(const std::string &string) const;

private:
    bool _isFormula(const std::string &string) const;

    bool _isInteger(const std::string &s) const;

    bool _isDecimal(const std::string &s) const;
};


