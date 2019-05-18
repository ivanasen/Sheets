#pragma once

#include <string>
#include <Table.h>

class FormulaCalculator {
public:
    static std::string calculateFormula(const std::string &formula, const Table &table);
};