cmake_minimum_required(VERSION 3.13)
project(Tests)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/TableCellTests.cpp src/main.cpp src/TableTests.cpp src/StringUtilsTests.cpp src/FormulaTests.cpp src/CsvSerializationTests.cpp)
add_executable(Tests ${SOURCE_FILES})

target_link_libraries(Tests PRIVATE Catch Core Serialization Utils)