cmake_minimum_required(VERSION 3.13)

project(window
        VERSION 1.0
        LANGUAGES CXX)

file(GLOB_RECURSE SOURCES source/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h)

add_library(${PROJECT_NAME} STATIC
               ${HEADERS}
               ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PUBLIC glfw glad::glad)
