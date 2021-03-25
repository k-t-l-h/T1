#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "libs/naive/check.h"

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

    while ((opt = getopt(argc, argv, opts)) != -1) {
        switch (opt) {
                //TODO: сделать его не обязательным
            case 'p':
                //здесь обработка числа потоков
                //и проверка корректности
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

    //наивная реализация
    printf("%d", check(predicate, arr, num));


    return 0;
}