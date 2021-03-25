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
add_library(PREDICATE_CHECK_P SHARED libs/parallel/check_p.c)



add_executable(T1 main.c)
include_directories(libs)

if (ENABLE_TESTS)
    enable_testing()

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

endif()

