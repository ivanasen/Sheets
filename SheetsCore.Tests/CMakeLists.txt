cmake_minimum_required(VERSION 3.14)
project(SheetsCore.Tests)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/TableCellTests.cpp src/main.cpp src/TableTests.cpp src/StringUtilsTests.cpp src/FormulaTests.cpp)
add_executable(SheetsCore.Tests ${SOURCE_FILES})

target_link_libraries(SheetsCore.Tests PRIVATE Catch SheetsCore)