cmake_minimum_required(VERSION 3.14)
project(SheetsCore)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/Table.cpp include/Table.h src/CellType.h src/TableCellParser.cpp src/TableCellParser.h src/StringUtils.cpp src/TableFormulaCalculator.cpp src/TableFormulaCalculator.h src/TokenType.h src/TokenValues.h src/Token.cpp src/Token.h src/TableFormulaParser.cpp src/TableFormulaParser.h src/Constants.cpp src/TableCell.cpp src/ArithmeticFormulasUtils.cpp src/ArithmeticFormulasUtils.h src/StringUtils.h src/FormulaTableCell.cpp src/FormulaTableCell.h src/TableCellPosition.cpp src/TableCellPosition.h)

include_directories(${PROJECT_SOURCE_DIR}/include/)

add_library(SheetsCore STATIC ${SOURCE_FILES})

target_include_directories(SheetsCore INTERFACE ${PROJECT_SOURCE_DIR}/include/)
