cmake_minimum_required(VERSION 3.10)
project(T1)

add_executable(T1 src/main.c)
#добавить текстовый файлик
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/data.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/incorrect_data.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#тестирование
enable_testing()
add_test(NAME AllGood
        COMMAND T1 ../src/data.txt Russia)
set_tests_properties(AllGood PROPERTIES
        PASS_REGULAR_EXPRESSION
        "Name: Toy\nPrice: 2.000000\nAvaliable: 1073741824\nCountry: Russia\n")

add_test(NAME OneArg
        COMMAND T1 ../src/data.txt )
set_tests_properties(OneArg PROPERTIES
        PASS_REGULAR_EXPRESSION "Not enough arguments\n")

add_test(NAME FileNotFound
        COMMAND T1 ../src/incorrect_data.txt Russia)
set_tests_properties(FileNotFound PROPERTIES
        PASS_REGULAR_EXPRESSION "Incorrect data format\n")


