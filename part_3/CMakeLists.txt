cmake_minimum_required(VERSION 3.13)
project(part_3 C)

set(CMAKE_C_STANDARD 99)

add_executable(part_3 map.h map.c node.c node.h main.c)