cmake_minimum_required(VERSION 3.10)
project(T1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "--coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -Werror -Wpedantic")

#здесь статическая библиотека
add_library(PREDICATE_CHECK STATIC libs/naive/check.c)
#здесь динамическая библиотека
add_library(PREDICATE_CHECK_P SHARED libs/parallel/check_p.c libs/parallel/pipes.c)

file(COPY data/data.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


add_executable(T1 main.c)
target_link_libraries(T1 ${CMAKE_DL_LIBS} PREDICATE_CHECK PREDICATE_CHECK_P)

if (ENABLE_TESTS)
    enable_testing()

    #наивная реализация
    set(LIB_SOURCE_FILES libs/naive/check.c libs/naive/test_check.cpp)
    add_library(url_parse_std_lib STATIC ${LIB_SOURCE_FILES})
    link_libraries(gcov)

    find_package(GTest REQUIRED)

    include_directories(${GTEST_INCLUDE_DIRS})
    add_executable(test_check.out libs/naive/test_check.cpp)
    target_link_libraries(test_check.out url_parse_std_lib)

    target_link_libraries(test_check.out ${GTEST_LIBRARIES})
    target_link_libraries(test_check.out pthread)

    add_test(test_check.out test_check.out)

    #параллельная реализация
    set(LIB_SOURCE_FILES_2 libs/parallel/check_p.c libs/parallel/pipes.c libs/parallel/test_check_p.cpp)
    add_library(url_parse_std_lib_2 SHARED ${LIB_SOURCE_FILES_2})
    link_libraries(gcov)
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
    add_executable(test_check_p.out libs/parallel/test_check_p.cpp)
    target_link_libraries(test_check_p.out url_parse_std_lib_2)

    target_link_libraries(test_check_p.out ${GTEST_LIBRARIES})
    target_link_libraries(test_check_p.out pthread)

    add_test(test_check_p.out test_check_p.out)
endif()

