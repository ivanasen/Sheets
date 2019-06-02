cmake_minimum_required(VERSION 3.14)
project(Core)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/Table.cpp include/Table.h src/CellType.h src/TokenType.h src/TokenValues.h src/Token.cpp src/Token.h src/ArithmeticFormulasUtils.cpp src/ArithmeticFormulasUtils.h src/FormulaTableCell.cpp src/TableCellPosition.cpp src/TableCellPosition.h src/exceptions/TableCellRangeException.cpp src/exceptions/TableCellRangeException.h src/DecimalTableCell.cpp src/DecimalTableCell.h src/IntegerTableCell.cpp src/IntegerTableCell.h src/StringTableCell.cpp src/StringTableCell.h)

include_directories(${PROJECT_SOURCE_DIR}/include/)

add_library(Core STATIC ${SOURCE_FILES})

target_link_libraries(Core PRIVATE Utils)

target_include_directories(Core INTERFACE ${PROJECT_SOURCE_DIR}/include/)
