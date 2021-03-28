#include <dlfcn.h> //для работы с динамической библиотекой
#include "libs/naive/check.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/*
 * Вариант #7
 * В вашем распоряжении — массив из 100 млн. чисел.
 * Необходимо подсчитать количество таких чисел,
 * которые обращают в истину заданный предикат (например, x < 157).
 * Реализуйте наивный алгоритм последовательного подсчёта
 * и параллельный алгоритм, использующий несколько процессов,
 * с учётом оптимизации работы с кэш-памятью.
 */

//откуда считать и сколько считать
int* read_from_file(char* filename, size_t num) {
    FILE* fp = NULL;
    fp = fopen(filename, "r");
    if (NULL == fp) {
        printf("file not found");
        return NULL;
    };

    int* arr = (int*)calloc(num, sizeof(int*));
    //считать из файла
    for (size_t i = 0; i < num; ++i) {
        if (fscanf(fp, "%d", &arr[i]) != 1) {
            printf("not enough nums!");
            free(arr);
            fclose(fp);
            return NULL;
        }
    }

    fclose(fp);
    return arr;
}

int predicate(int a) {
    if (a > 0 ) {
        return 1;
    }
    return 0;
}

int main(int argc, char** argv) {
    int opt, n;
    //: - имеет значение ::- возможно имеет значение

    //флаги
    //t - количество потоков (не обязательно)
    //n - число чисел
    //f - откуда брать числа
    char* opts = "t:n:f:";
    char * filename = "";
    size_t num = 0;
    size_t threads_num = 0;

    while ((opt = getopt(argc, argv, opts)) != -1) {
        switch (opt) {
            case 't':
                threads_num = atoi(optarg);
                printf("%d\n", threads_num);
                break;
            case 'n':
                num = atoi(optarg);
                printf("%d\n", num);
                //здесь обработка числа чисел
                break;
            case 'f':
                filename = optarg;
                printf("%s\n", filename);
                //здесь проверка на файл
                //на открытие файла
                //на валидность
                break;
        }
    }
    int* arr = read_from_file(filename, num);
    if (arr == NULL) {
        return -1;
    }

    clock_t start_t, end_t, total_t;
    //наивная реализация
    start_t = clock();
    size_t result = 0;
    printf("%d", check(predicate, arr, num, &result));
    end_t = clock();
    total_t = (end_t - start_t) / CLOCKS_PER_SEC;
    printf("Time taken: %ld", total_t);

    //работа с динамической библиотекой


    void *library;
    library = dlopen("checks.so", RTLD_NOW);
    if (NULL == library) {
      free(arr);
      printf("Библиотека checks.so была не найдена, вернитесь позже");
      return -1;
    }
    //создаем указатель на функцию
    int summ = 0;
    int (*check_p)(int (*f)(int), int* arr, size_t arr_size, size_t* summ);
    check_p = dlsym(library, "check_p");

    //прогоняем тесты
    start_t = clock();
    printf("%d", check_p(predicate, arr, num, &threads_num));
    end_t = clock();
    total_t = (end_t - start_t) / CLOCKS_PER_SEC;
    printf("Время, затраченное параллельной реализацией: %ld", total_t);

    dlclose(library);

    free(arr);

  return 0;
}