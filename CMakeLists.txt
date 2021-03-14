cmake_minimum_required(VERSION 3.10)
project(T1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "--coverage")
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wpedantic")

include(ExternalProject)
add_executable(T1 src/main.c)
#добавить текстовый файлик
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/data.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/incorrect_data.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#Если мы хотим потестировать файлик
if (ENABLE_TESTS)
    message("Tests enabled")
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
endif ()


#включаем статический анализ
if (ENABLE_STATIC_CHECK)
    message("CPPCheck enabled")

    list(APPEND CPPCHECK_CMAKE_ARGS
            "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}"
            )

    ExternalProject_Add(
            cppcheck
            GIT_REPOSITORY      https://github.com/danmar/cppcheck.git
            GIT_TAG             2.3
            GIT_SHALLOW         1
            CMAKE_ARGS          ${CPPCHECK_CMAKE_ARGS}
            PREFIX              ${CMAKE_BINARY_DIR}/external/cppcheck/prefix
            TMP_DIR             ${CMAKE_BINARY_DIR}/external/cppcheck/tmp
            STAMP_DIR           ${CMAKE_BINARY_DIR}/external/cppcheck/stamp
            DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/cppcheck/download
            SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/cppcheck/src
            BINARY_DIR          ${CMAKE_BINARY_DIR}/external/cppcheck/build
    )

    list(APPEND CPPCHECK_ARGS
            --enable=warning,style,unusedFunction,missingInclude
            --inconclusive #проверяем маловероятные
            --std=c++11
            --verbose #более подробный анализ
            --error-exitcode=1 #роняем тесты
            --language=c++
            -I ${CMAKE_SOURCE_DIR}/include
            ${CMAKE_SOURCE_DIR}/src/*.c
            )


endif ()


#включаем
if (ENABLE_VALGRIND_CHECK)
    message("Valgrind enabled")
    find_program(VALGRIND valgrind REQUIRED)

    if(VALGRIND)
        message("Valgrind found")
        set(VALGRIND_OPTIONS "--leak-check=full --track-origins=yes --error-exitcode=1")
    endif ()

endif ()
