cmake_minimum_required(VERSION 3.13)

project(tester
        VERSION 1.0
        LANGUAGES CXX)

add_compile_options(
        # -Werror
        # -Wpaded?
        -Wall
        -Wextra
        -Wpedantic
        -Wcast-align
        -Wcast-qual
        -Wconversion
        -Wctor-dtor-privacy
        -Wenum-compare
        -Wfloat-equal
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Woverloaded-virtual
        -Wredundant-decls
        -Wsign-conversion
        -Wsign-promo)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

set(HEADERS
        include/test.h
        include/test_case.h
)

set(SOURCES
        source/test.cpp
        source/test_case.cpp
)

add_library(${PROJECT_NAME} STATIC
        ${HEADERS}
        ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

#add_subdirectory("test")
