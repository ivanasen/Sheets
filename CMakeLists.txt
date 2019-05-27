cmake_minimum_required(VERSION 3.14)
project(Sheets)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Core)
add_subdirectory(Cli)
add_subdirectory(Utils)
add_subdirectory(Serialization)
add_subdirectory(Tests)
add_subdirectory(lib/catch)