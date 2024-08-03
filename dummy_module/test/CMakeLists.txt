cmake_minimum_required(VERSION 3.13)

project(dummy-lib-test
        VERSION 1.0
        LANGUAGES CXX)

set(TEST1 test-dummy-1)

add_executable(${TEST1} test.cpp)

target_link_libraries(${TEST1} dummy)

add_test(dummy-1 ${TEST1})

# NOTE(Akumanory): Example if you want to run test while building
# actually it is POST BUILD but still does what I have in mind for now
# add_custom_command(TARGET ${TEST1}
#                    POST_BUILD
#                    COMMAND ctest -C $<CONFIGURATION>)
