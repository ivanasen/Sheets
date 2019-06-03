cmake_minimum_required(VERSION 3.13)
project(Sheets)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src/Core)
add_subdirectory(src/Cli)
add_subdirectory(src/Utils)
add_subdirectory(src/Serialization)
add_subdirectory(src/Tests)
add_subdirectory(lib/catch)