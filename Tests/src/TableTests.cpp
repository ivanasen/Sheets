#include <catch.hpp>
#include <Table.h>

using namespace SheetsCore;

TEST_CASE("Table value setting and getting works correctly", "[Table]") {
    std::string expected = "Pesho";
    Table table(10, 10);
    table.setCellValue(TableCellPosition(0, 0), expected);

    REQUIRE(expected == table.getCellValue(TableCellPosition(0, 0)));
}

TEST_CASE("Table resizes when which is out of current bounds is set", "[Table]") {
    std::string expected = "Pesho";
    Table table(10, 10);
    table.setCellValue(TableCellPosition(Table::MAX_SIZE - 1, Table::MAX_SIZE - 1), expected);

    REQUIRE(expected == table.getCellValue(TableCellPosition(Table::MAX_SIZE - 1, Table::MAX_SIZE - 1)));
}


TEST_CASE("Table can do simple arithmetic formulas", "[Table]") {
    std::string formula = "= 3 + 5";
    double expected = 8;

    Table table;

    table.setCellValue(TableCellPosition(0, 0), formula);
    std::string cellValue = table.getCellValue(TableCellPosition(0, 0));

    REQUIRE(expected == std::stod(cellValue));
}