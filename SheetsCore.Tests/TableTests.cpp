#include <catch.hpp>
#include <Table.h>

TEST_CASE("Table value setting and getting works correctly", "[Table]") {
    std::string expected = "Pesho";
    Table table(10, 10);
    table.setCellValue(0, 0, expected);

    REQUIRE(expected == table.getCell(0, 0).getValue());
}

TEST_CASE("Table resizes when which is out of current bounds is set", "[Table]") {
    std::string expected = "Pesho";
    Table table(10, 10);
    table.setCellValue(1000, 1000, expected);

    REQUIRE(expected == table.getCell(1000, 1000).getValue());
}