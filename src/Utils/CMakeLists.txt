cmake_minimum_required(VERSION 3.13)
project(Utils)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/Strings.cpp src/Files.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include/)

add_library(Utils STATIC ${SOURCE_FILES})

target_include_directories(Utils INTERFACE ${PROJECT_SOURCE_DIR}/include/)
