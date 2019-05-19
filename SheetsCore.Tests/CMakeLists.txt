cmake_minimum_required(VERSION 3.14)
project(SheetsCore.Tests)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES TableCellTests.cpp main.cpp TableTests.cpp StringUtilsTests.cpp FormulaTests.cpp)
add_executable(SheetsCore.Tests ${SOURCE_FILES})

target_link_libraries(SheetsCore.Tests PRIVATE Catch SheetsCore)