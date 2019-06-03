#include <catch.hpp>
#include <TableCell.h>
#include <../../Core/src/TableCells/StringTableCell.h>

using namespace core;

TEST_CASE("TableCell works correctly", "[TableCell]") {
    std::string value = "Pesho";
    StringTableCell cell(value);
    REQUIRE(value == cell.getDisplayValue());
}