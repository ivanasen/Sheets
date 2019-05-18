#include <catch.hpp>
#include <TableCell.h>
#include "../SheetsCore/src/TableCellParser.h"

TEST_CASE("TableCell works correctly", "[TableCell]") {
    std::string value = "Pesho";
    TableCell cell(CellType::STRING, value);
    REQUIRE(value == cell.getValue());
}

TEST_CASE("TableCellParser parses integers correctly", "[TableCellParser]") {
    TableCellParser tableCellParser;

    TableCell cell1 = tableCellParser.parse("23");
    REQUIRE(cell1.getType() == CellType::INTEGER);

    TableCell cell2 = tableCellParser.parse("0");
    REQUIRE(cell2.getType() == CellType::INTEGER);

    TableCell cell3 = tableCellParser.parse("34354545354352432432");
    REQUIRE(cell3.getType() == CellType::INTEGER);

    TableCell cell4 = tableCellParser.parse("    12324      ");
    REQUIRE(cell4.getType() == CellType::INTEGER);
}

TEST_CASE("TableCellParser parses decimals correctly", "[TableCellParser]") {
    TableCellParser tableCellParser;

    TableCell cell1 = tableCellParser.parse("23.23");
    REQUIRE(cell1.getType() == CellType::DECIMAL);

    TableCell cell2 = tableCellParser.parse("0.231");
    REQUIRE(cell2.getType() == CellType::DECIMAL);

    TableCell cell3 = tableCellParser.parse(".4354545354352432432");
    REQUIRE(cell3.getType() == CellType::DECIMAL);

    TableCell cell4 = tableCellParser.parse("    12324.124255435      ");
    REQUIRE(cell4.getType() == CellType::DECIMAL);
}

TEST_CASE("TableCellParser parses strings correctly", "[TableCellParser]") {
    TableCellParser tableCellParser;

    TableCell cell1 = tableCellParser.parse("Pesho");
    REQUIRE(cell1.getType() == CellType::STRING);

    TableCell cell2 = tableCellParser.parse("0.23123432f34324");
    REQUIRE(cell2.getType() == CellType::STRING);

    TableCell cell3 = tableCellParser.parse("24.4354.545354352432432");
    REQUIRE(cell3.getType() == CellType::STRING);

    TableCell cell4 = tableCellParser.parse("== 34 + 2 - 2E + B3 + c4 (");
    REQUIRE(cell4.getType() == CellType::STRING);
}