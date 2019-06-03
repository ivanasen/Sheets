#include <catch.hpp>
#include <CsvFormatter.h>
#include <../../Core/src/TableCellPosition.h>
#include <Table.h>

TEST_CASE("SerializeCsv", "[CsvTableFormatting]") {
    core::Table table(3, 3);
    table.setCellValue(core::TableCellPosition(0, 0), "Pesho's \"");
    table.setCellValue(core::TableCellPosition(1, 0), "12");
    table.setCellValue(core::TableCellPosition(2, 1), "12.3455645");
    table.setCellValue(core::TableCellPosition(2, 2), "= R2C1 + 232.35 * R3C2 - 354");

    std::string serialized = serialization::CsvFormatter::serialize(table);
    std::string expected = "\"Pesho's \\\"\",,,\n"
                           "12,,,\n"
                           ",12.345565,= R2C1 + 232.35 * R3C2 - 354,\n";

    REQUIRE(expected == serialized);
}

TEST_CASE("DeserializeCsv", "[CsvTableFormatting]") {
    std::string serialized = " , , ,\n"
                             " , ,3.14,\n"
                             "3232,\"Hello World!\"          ,= R1C1 + 10 * R2C3 - 20,\n"
                             "\"Pesho, Gosho\\\" sdsd!?  \"        ";
    std::stringstream stream(serialized);
    core::Table table = serialization::CsvFormatter::deserialize(stream);

    REQUIRE(table.getCellDisplayValue(core::TableCellPosition(1, 2)) == "3.14");
    REQUIRE(table.getCellDisplayValue(core::TableCellPosition(2, 0)) == "3232");
    REQUIRE(table.getCellDisplayValue(core::TableCellPosition(2, 1)) == "Hello World!");
    REQUIRE(table.getCellDisplayValue(core::TableCellPosition(3, 0)) == "Pesho, Gosho\" sdsd!?  ");
    std::string formulaResult = table.getCellDisplayValue(core::TableCellPosition(2, 2));
    REQUIRE(std::stod(formulaResult) == 11.4);
}

