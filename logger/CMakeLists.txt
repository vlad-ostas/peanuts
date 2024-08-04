cmake_minimum_required(VERSION 3.13)

project(logger
        VERSION 1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# GCC style
# add_compile_options(
#     # -Werror
#     # -Wpaded?
#     -Wall
#     -Wextra
#     -Wpedantic
#     -Wcast-align
#     -Wcast-qual
#     -Wconversion
#     -Wctor-dtor-privacy
#     -Wenum-compare
#     -Wfloat-equal
#     -Wnon-virtual-dtor
#     -Wold-style-cast
#     -Woverloaded-virtual
#     -Wredundant-decls
#     -Wsign-conversion
#     -Wsign-promo)

# MSVC style
add_compile_options()

if(NOT CMAKE_CXX_EXTENSIONS)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

# set(HEADERS
#     include/*.h)

# set(SOURCES
#     source/*.cpp
#     main.cpp)

# NOTE(akumanory): 
# GLOB_RECURSE searces recursevly in given directory for the given pattern
# can be used as an upgrade for 'set' in projects that uses 'include' and 'source' pattern

file(GLOB_RECURSE SOURCES source/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h)

add_library(${PROJECT_NAME} STATIC
               ${HEADERS}
               ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

add_subdirectory("test")
