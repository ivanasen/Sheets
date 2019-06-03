cmake_minimum_required(VERSION 3.13)
project(Core)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/Table.cpp include/Table.h src/CellType.h src/Token.cpp src/ArithmeticFormulasUtils.cpp src/ArithmeticFormulasUtils.h src/TableCells/FormulaTableCell.cpp src/TableCellPosition.cpp src/TableCellPosition.h src/exceptions/TableCellRangeException.cpp src/exceptions/TableCellRangeException.h src/TableCells/DecimalTableCell.cpp src/TableCells/DecimalTableCell.h src/TableCells/IntegerTableCell.cpp src/TableCells/IntegerTableCell.h src/TableCells/StringTableCell.cpp src/TableCells/StringTableCell.h src/Cloneable.h)

include_directories(${PROJECT_SOURCE_DIR}/include/)

add_library(Core STATIC ${SOURCE_FILES})

target_link_libraries(Core PRIVATE Utils)

target_include_directories(Core INTERFACE ${PROJECT_SOURCE_DIR}/include/)
