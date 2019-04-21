cmake_minimum_required(VERSION 3.13)
project(part_4 C)

set(CMAKE_C_STANDARD 99)

add_executable(part_4 main.c eurovision.h list.h set.h eurovision.c)
find_library(myLib libmtm.a)
target_link_libraries(part_4 ${mylib})