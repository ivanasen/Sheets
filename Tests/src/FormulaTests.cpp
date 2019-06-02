#include <catch.hpp>
#include <Table.h>
#include <FormulaTableCell.h>

using namespace core;

TEST_CASE("tokenizeFormula", "[FormulaTableCell]") {
    Table table;
    std::string f1 = "= 3 + 5";
    std::string expected1 = "8.00";
    FormulaTableCell cell1(f1, TableCellPosition(0, 0), table);

    REQUIRE(expected1 == cell1.getDisplayValue());

    std::string f2 = "= (3 + 5) * 3.14 - 523435.354 + 2.141";
    std::string expected2 = "-523408.09";
    FormulaTableCell cell2(f2, TableCellPosition(0, 0), table);

    REQUIRE(expected2 == cell2.getDisplayValue());
}