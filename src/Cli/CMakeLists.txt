cmake_minimum_required(VERSION 3.13)
project(Cli)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_SOURCES src/main.cpp src/SheetsClient.cpp src/SheetsClient.h src/Client.cpp src/Client.h src/Commands.cpp src/Commands.h src/TableManager.cpp src/TableManager.h src/Constants.cpp src/Constants.h src/Log.cpp src/Log.h)
add_executable(Cli ${PROJECT_SOURCES})

target_link_libraries(Cli PRIVATE Core Serialization Utils)