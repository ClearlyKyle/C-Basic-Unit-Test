cmake_minimum_required(VERSION 3.10)

project(C_UNIT_TESTS)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(${CMAKE_PROJECT_NAME} main.c unit_test.c unit_test.h)