cmake_minimum_required(VERSION 3.14)
project(SheetsCore)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/IntegerTableCell.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include/)

add_library(SheetsCore STATIC ${SOURCE_FILES})

target_include_directories(SheetsCore INTERFACE ${PROJECT_SOURCE_DIR}/include/)
