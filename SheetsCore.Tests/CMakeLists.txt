cmake_minimum_required(VERSION 3.14)
project(SheetsCore.Tests)

set(CMAKE_CXX_STANDARD 17)

include_directories(lib/catch2)
include_directories(../SheetsCore)

set(SOURCE_FILES main.cpp)
add_executable(SheetsCore.TestsRun ${SOURCE_FILES})