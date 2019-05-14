cmake_minimum_required(VERSION 3.14)
project(Sheets)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(SheetsCore)
add_subdirectory(SheetsCore.Tests)
add_subdirectory(lib/catch)