#include <dlfcn.h> //для работы с динамической библиотекой
#include "libs/naive/check.h"
#include <stdio.h>
#include <stdlib.h>
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
    printf("File not found\n");
    return NULL;
  }

  int* arr = (int*)calloc(num, sizeof(int*));
  if (NULL == arr) {
    close(fp);
    return NULL;
  }
  
  //считать из файла
  for (size_t i = 0; i < num; ++i) {
    if (fscanf(fp, "%d", &arr[i]) != 1) {
      printf("Not enough numbers!\n");
      free(arr);
      fclose(fp);
      return NULL;
    }
  }

  fclose(fp);
  return arr;
}

int predicate(int a) {
  if (a > 0) {
    return 1;
  }
  return 0;
}

int main(int argc, char** argv) {
  int opt, n;
  //: - имеет значение ::- возможно имеет значение

  //флаги
  // n - число чисел
  // f - откуда брать числа
  char* opts = "n:f:";
  char* filename = "";
  size_t num = 0;

  while ((opt = getopt(argc, argv, opts)) != -1) {
    switch (opt) {
    case 'n':
      num = atoi(optarg);
      if (num <= 0) {
        printf("Incorrect number of numbers!\n");
        return -1;
      }
      break;
    case 'f':
      filename = optarg;
      break;
    default:
      break;
    }
  }

  int* arr = read_from_file(filename, num);
  if (arr == NULL) {
    return -1;
  }

  clock_t start_t, end_t;
  //наивная реализация
  start_t = clock();
  size_t result = 0;
  int code = check(predicate, arr, num, &result);
  printf("(Naive version) Return code: %d, result: %zu\n", code, result);
  end_t = clock();
  double total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
  printf("(Naive version) Time taken: %lf\n", total_t);

  //работа с динамической библиотекой
  void* library;
  library = dlopen("./libPREDICATE_CHECK_P.so", RTLD_NOW);
  if (NULL == library) {
    free(arr);
    printf("Lib ./libPREDICATE_CHECK_P.so not found :(\n");
    return -1;
  }
  //создаем указатель на функцию
  int (*check_p)(int (*f)(int), int* arr, size_t arr_size, size_t* summ);
  check_p = dlsym(library, "check_p");

  //прогоняем тесты
  start_t = clock();
  code = check_p(predicate, arr, num, &result);
  printf("(Parallel version) Return code: %d, result: %zu\n", code, result);
  end_t = clock();
  total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
  printf("(Parallel version) Time taken: %lf\n", total_t);

  dlclose(library);

  free(arr);

  return 0;
}