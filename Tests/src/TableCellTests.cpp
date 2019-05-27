#include <catch.hpp>
#include <TableCell.h>

using namespace core;

TEST_CASE("TableCell works correctly", "[TableCell]") {
    std::string value = "Pesho";
    TableCell cell(CellType::STRING, value);
    REQUIRE(value == cell.getValue());
}