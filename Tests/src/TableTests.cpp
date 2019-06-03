#include <catch.hpp>
#include <Table.h>

using namespace core;

TEST_CASE("Table value setting and getting works correctly", "[Table]") {
    std::string expected = "Pesho";
    Table table(10, 10);
    table.setCellValue(0, 0, expected);

    REQUIRE(expected == table.getCellDisplayValue(0, 0));
}

TEST_CASE("Table resizes when which is out of current bounds is set", "[Table]") {
    std::string expected = "Pesho";
    Table table(10, 10);
    table.setCellValue(1000, 1000, expected);

    REQUIRE(expected == table.getCellDisplayValue(1000, 1000));
}


TEST_CASE("Table can do simple arithmetic formulas", "[Table]") {
    std::string formula = "= 3 + 5";
    double expected = 8;

    Table table;

    table.setCellValue(0, 0, formula);
    std::string cellValue = table.getCellDisplayValue(0, 0);

    REQUIRE(expected == std::stod(cellValue));
}