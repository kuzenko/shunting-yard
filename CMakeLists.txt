cmake_minimum_required(VERSION 3.13)
project(shuntingYard)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(ShuntingYardCore)

enable_testing()

option(SHUNTINGYARD_BUILD_GOOGLETEST "Build googletest" ON)

add_subdirectory(tests)
