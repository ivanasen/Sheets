cmake_minimum_required(VERSION 3.14)
project(Utils)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES)

include_directories(${PROJECT_SOURCE_DIR}/include/)

add_library(Utils INTERFACE)

target_include_directories(Utils INTERFACE ${PROJECT_SOURCE_DIR}/include/)

