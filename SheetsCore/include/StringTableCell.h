#pragma once

#include <string>
#include "TableCell.h"

class StringTableCell : public TableCell {
public:
    explicit StringTableCell(std::string value);

    std::string getValue() override;

    void setValue(const std::string &value) override;

private:
    std::string _value;
};