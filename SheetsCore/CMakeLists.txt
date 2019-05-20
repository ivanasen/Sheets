cmake_minimum_required(VERSION 3.14)
project(SheetsCore)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/Table.cpp include/Table.h src/CellType.h src/TokenType.h src/TokenValues.h src/Token.cpp src/Token.h src/TableCell.cpp src/ArithmeticFormulasUtils.cpp src/ArithmeticFormulasUtils.h src/FormulaTableCell.cpp src/FormulaTableCell.h src/TableCellPosition.cpp src/TableCellPosition.h src/exceptions/TableCellRangeException.cpp src/exceptions/TableCellRangeException.h)

include_directories(${PROJECT_SOURCE_DIR}/include/)

add_library(SheetsCore STATIC ${SOURCE_FILES})

target_link_libraries(SheetsCore PRIVATE Utils)

target_include_directories(SheetsCore INTERFACE ${PROJECT_SOURCE_DIR}/include/)
