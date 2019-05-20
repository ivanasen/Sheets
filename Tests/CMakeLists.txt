cmake_minimum_required(VERSION 3.14)
project(Tests)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/TableCellTests.cpp src/main.cpp src/TableTests.cpp src/StringUtilsTests.cpp src/FormulaTests.cpp)
add_executable(Tests ${SOURCE_FILES})

target_link_libraries(Tests PRIVATE Catch SheetsCore Utils)