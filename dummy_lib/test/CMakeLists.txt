cmake_minimum_required(VERSION 3.13)

project(dummy-lib-test
        VERSION 1.0
        LANGUAGES CXX)

set(TEST1 test-dummy-lib-1)

add_executable(${TEST1} test.cpp)

target_link_libraries(${TEST1} dummy-lib)

add_test(dummy-lib-1 ${TEST1})

# add_custom_command(TARGET ${TEST1}
#                    POST_BUILD
#                    COMMAND ctest -C $<CONFIGURATION>)
