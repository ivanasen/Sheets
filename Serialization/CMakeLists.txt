cmake_minimum_required(VERSION 3.14)
project(Serialization)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/CsvTableFormatting.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include/)

add_library(Serialization STATIC ${SOURCE_FILES})

target_link_libraries(Serialization PRIVATE Core Utils)

target_include_directories(Serialization INTERFACE ${PROJECT_SOURCE_DIR}/include/)
