#include <catch.hpp>
#include <CsvTableFormatting.h>
#include <../../Core/src/TableCellPosition.h>
#include <Table.h>

TEST_CASE("SerializeCsv", "[CsvTableFormatting]") {
    core::Table table(3, 3);
    table.setCellValue(core::TableCellPosition(0, 0), "Pesho");
    table.setCellValue(core::TableCellPosition(1, 0), "12");
    table.setCellValue(core::TableCellPosition(2, 1), "12.3455645");
    table.setCellValue(core::TableCellPosition(2, 2), "= R2C1 + 232.35 * R3C2 - 354");

    std::string serialized = serialization::csv::serialize(table);
    std::string expected = "Pesho,,,\n"
                           "12,,,\n"
                           ",12.3455645,= R2C1 + 232.35 * R3C2 - 354,\n";

    REQUIRE(serialized == expected);
}

TEST_CASE("DeserializeCsv", "[CsvTableFormatting]") {
    std::string serialized = " , , ,\n"
                             " , ,3.14,\n"
                             "3232,Hello World!,= R1C1 + 10 * R2C3 - 20,\n";
    core::Table table = serialization::csv::deserialize(serialized);

    REQUIRE(table.getCellValue(core::TableCellPosition(1, 2)) == "3.14");
    REQUIRE(table.getCellValue(core::TableCellPosition(2, 0)) == "3232");
    REQUIRE(table.getCellValue(core::TableCellPosition(2, 1)) == "Hello World!");
    std::string formulaResult = table.getCellValue(core::TableCellPosition(2, 2));
    REQUIRE(std::stod(formulaResult) == 11.4);
}

