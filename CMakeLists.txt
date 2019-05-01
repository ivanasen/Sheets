cmake_minimum_required(VERSION 3.14)
project(Sheets)

set(CMAKE_CXX_STANDARD 17)

include_directories(Sheets)

add_subdirectory(SheetsCore)
add_subdirectory(SheetsCore.Tests)

set(SOURCE_FILES Cli/main.cpp)
add_executable(SheetsRun ${SOURCE_FILES})

target_link_libraries(SheetsRun SheetsCore)