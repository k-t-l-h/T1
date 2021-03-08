cmake_minimum_required(VERSION 3.13)
project(T1)

add_executable(T1 src/main.c)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/data.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})