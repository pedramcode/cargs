cmake_minimum_required(VERSION 3.10)
project(cargs)

file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)