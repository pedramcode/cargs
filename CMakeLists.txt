cmake_minimum_required(VERSION 3.10)
project(cargs)

file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)

add_executable(${PROJECT_NAME} ${SOURCES} include/cargs/cargs.h src/cargs.c)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)