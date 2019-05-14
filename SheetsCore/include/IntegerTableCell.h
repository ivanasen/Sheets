#pragma once

#include "TableCell.h"

class IntegerTableCell : public TableCell {
public:
    explicit IntegerTableCell(int value);

    std::string getValue() override;

    void setValue(const std::string &value) override;

private:
    int _value;
};
