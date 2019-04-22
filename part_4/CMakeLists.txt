cmake_minimum_required(VERSION 3.13)
project(part_4 C)

set(CMAKE_C_STANDARD 99)

add_executable(part_4 main.c eurovision.h list.h set.h eurovision.c judge.c judge.h stateScore.c stateScore.h state.c state.h stateVotes.c stateVotes.h friendlyStates.c friendlyStates.h /tests/eurovisionTests.c /tests/eurovisionTestsMain.c /tests/test_utilities.h)
target_link_libraries(part_4 ${CMAKE_SOURCE_DIR}/libmtm.a)