#pragma once

class TableCell {
public:
    virtual std::string getValue() = 0;

    virtual void setValue(const std::string &value) = 0;
};