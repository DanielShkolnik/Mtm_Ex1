cmake_minimum_required(VERSION 3.13)
project(part_4 C)

set(CMAKE_C_STANDARD 99)

add_executable(part_4 eurovision.h list.h set.h eurovision.c judge.c judge.h stateScore.c stateScore.h state.c state.h stateVotes.c stateVotes.h friendlyStates.c friendlyStates.h
        ${CMAKE_SOURCE_DIR}/tests/eurovisionTests ${CMAKE_SOURCE_DIR}/tests/eurovisionTestsMain ${CMAKE_SOURCE_DIR}/tests/test_utilities)
target_link_libraries(part_4 ${CMAKE_SOURCE_DIR}/libmtm.a)