#include <catch.hpp>
#include <StringTableCell.h>
#include <IntegerTableCell.h>
#include <DoubleTableCell.h>

TEST_CASE("StringTableCell works correctly", "[TableCell]") {
    std::string value = "Pesho";
    StringTableCell cell(value);
    REQUIRE(value == cell.getValue());
}

TEST_CASE("IntegerTableCell works correctly", "[TableCell]") {
    int value = 34;
    IntegerTableCell cell(value);
    REQUIRE(value == std::stoi(cell.getValue()));
}

TEST_CASE("DoubleTableCell works correctly", "[TableCell]") {
    double value = 3.141592;
    DoubleTableCell cell(value);
    REQUIRE(value == std::stod(cell.getValue()));
}
