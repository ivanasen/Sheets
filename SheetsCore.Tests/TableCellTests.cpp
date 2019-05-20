#include <catch.hpp>
#include <TableCell.h>
#include "../SheetsCore/src/TableCellParser.h"

using namespace SheetsCore;

TEST_CASE("TableCell works correctly", "[TableCell]") {
    std::string value = "Pesho";
    TableCell cell(0, 0, CellType::STRING, value);
    REQUIRE(value == cell.getValue());
}

TEST_CASE("TableCellParser parses integers correctly", "[TableCellParser]") {
    TableCell cell1 = TableCellParser::parse(0, 0, "23");
    REQUIRE(cell1.getType() == CellType::INTEGER);

    TableCell cell2 = TableCellParser::parse(0, 0, "0");
    REQUIRE(cell2.getType() == CellType::INTEGER);

    TableCell cell3 = TableCellParser::parse(0, 0, "34354545354352432432");
    REQUIRE(cell3.getType() == CellType::INTEGER);

    TableCell cell4 = TableCellParser::parse(0, 0, "    12324      ");
    REQUIRE(cell4.getType() == CellType::INTEGER);
}

TEST_CASE("TableCellParser parses decimals correctly", "[TableCellParser]") {
    TableCell cell1 = TableCellParser::parse(0, 0, "23.23");
    REQUIRE(cell1.getType() == CellType::DECIMAL);

    TableCell cell2 = TableCellParser::parse(0, 0, "0.231");
    REQUIRE(cell2.getType() == CellType::DECIMAL);

    TableCell cell3 = TableCellParser::parse(0, 0, ".4354545354352432432");
    REQUIRE(cell3.getType() == CellType::DECIMAL);

    TableCell cell4 = TableCellParser::parse(0, 0, "    12324.124255435      ");
    REQUIRE(cell4.getType() == CellType::DECIMAL);
}

TEST_CASE("TableCellParser parsers formulas correctly", "[TableCellParser]") {
    //All strings which start with an "=" sign should be recognized as formulas
    TableCell cell4 = TableCellParser::parse(0, 0, "= 34 + Pesho + 3432.45 - R3C2");
    REQUIRE(cell4.getType() == CellType::FORMULA);
}

TEST_CASE("TableCellParser parses strings correctly", "[TableCellParser]") {
    TableCell cell1 = TableCellParser::parse(0, 0, "Pesho");
    REQUIRE(cell1.getType() == CellType::STRING);

    TableCell cell2 = TableCellParser::parse(0, 0, "0.23123432f34324");
    REQUIRE(cell2.getType() == CellType::STRING);

    TableCell cell3 = TableCellParser::parse(0, 0, "24.4354.545354352432432");
    REQUIRE(cell3.getType() == CellType::STRING);
}