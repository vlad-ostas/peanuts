cmake_minimum_required(VERSION 3.13)

project(logger-test
        VERSION 1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TEST_BASIC test-logger-basic)

add_executable(${TEST_BASIC} test.cpp)

target_link_libraries(${TEST_BASIC} logger)

add_test(logger-basic ${TEST_BASIC})

# NOTE(Akumanory): Example if you want to run test while building
# actually it is POST BUILD but still does what I have in mind for now
# add_custom_command(TARGET ${TEST1}
#                    POST_BUILD
#                    COMMAND ctest -C $<CONFIGURATION>)
