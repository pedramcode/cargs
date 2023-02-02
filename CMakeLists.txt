cmake_minimum_required(VERSION 3.10)
project(cargs VERSION 0.1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_BUILD_TYPE Release)

file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/include/*.h)
install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION /usr/lib)
install(FILES ${HEADERS} DESTINATION /usr/include)