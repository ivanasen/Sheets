#include <catch.hpp>
#include "../../SheetsCore/src/Token.h"
#include "../../SheetsCore/src/FormulaTableCell.h"

using namespace SheetsCore;

TEST_CASE("tokenizeFormula", "[FormulaTableCell]") {
    Table table;
    std::string f1 = "= 3 + 5";
    std::string expected1 = std::to_string(8.0f);
    FormulaTableCell cell1(0, 0, f1, table);

    REQUIRE(expected1 == cell1.getValue());

    std::string f2 = "= (3 + 5) * 3.14 - 523435.354 + 2.141";
    std::string expected2 = std::to_string(-523408.093);
    FormulaTableCell cell2(0, 0, f2, table);

    REQUIRE(expected2 == cell2.getValue());
}