cmake_minimum_required(VERSION 3.13)

project(tester-test
        VERSION 0.1
        LANGUAGES CXX)

set(TEST1 test-tester-basic)

add_executable(${TEST1} basic-test.cpp)

target_link_libraries(${TEST1} tester)

add_test(tester-basic ${TEST1})

# NOTE(Akumanory): Example if you want to run test while building
# actually it is POST BUILD but still does what I have in mind for now
# add_custom_command(TARGET ${TEST1}
#                    POST_BUILD
#                    COMMAND ctest -C $<CONFIGURATION>)
