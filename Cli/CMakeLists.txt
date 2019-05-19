cmake_minimum_required(VERSION 3.14)
project(Cli)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_SOURCES src/main.cpp src/Log.h src/Log.cpp src/SheetsClient.cpp src/SheetsClient.h src/Client.cpp src/Client.h src/StringUtils.h src/StringUtils.cpp src/Commands.cpp src/Commands.h src/TableManager.cpp src/TableManager.h src/TableUtils.cpp src/TableUtils.h src/Constants.cpp src/Constants.h)
add_executable(Cli ${PROJECT_SOURCES})

target_link_libraries(Cli PRIVATE SheetsCore)