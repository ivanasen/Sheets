cmake_minimum_required(VERSION 3.14)
project(SheetsCore)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/Table.cpp include/Table.h src/CellType.h src/TableCellParser.cpp src/TableCellParser.h src/TableCell.cpp src/StringUtils.cpp src/FormulaCalculator.cpp src/FormulaCalculator.h src/TokenType.h src/TokenValues.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include/)

add_library(SheetsCore STATIC ${SOURCE_FILES})

target_include_directories(SheetsCore INTERFACE ${PROJECT_SOURCE_DIR}/include/)
