#include "check_p.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int check_predicate_range(int (*f)(int), int *arr, size_t begin, size_t end,
                          int *summ) {
  //нам передали что-то не то
  if (f == NULL || arr == NULL || summ == NULL) {
    return 1;
  }

  //на всякий случай обнуляем
  *summ = 0;

  for (size_t i = begin; i < end; ++i) {
    if (f(arr[i])) {
      *summ += 1;
    }
  }

  return 0;
}

//параллельная реализация с передаваемым числом
size_t check_p(int (*f)(int), int *arr, size_t arr_size, int *result) {
  *result = 0;

  if (arr == NULL || f == NULL) {
    return result;
  }

  //смотрим, сколько потоков мы можем сделать
  size_t process = sysconf(_SC_NPROCESSORS_ONLN);
  //создаем каналы
  pipes_t *pipes = create(process);
  if (pipes == NULL) {
    return result;
  }

  size_t part = (size_t)(arr_size / process);

  for (size_t i = 0; i < process; ++i) {
    int pid = fork();
    //не вышло
    if (pid == -1) {
      free_pipes(pipes);
      return result;
    }
    //вышло, мы в потомке
    if (pid == 0) {
      //разбить на несколько частей массив
      //для каждой части запустить поток

      size_t start = i * part;
      size_t end = i < process - 1 ? start + part : arr_size;
      int sum = 0;
      check_predicate_range(f, arr, start, end, sum);

      //получить из потока число
      //число вернуть
      //так можно, но нужно ли?..
      write(pipes->fd[i][1], &sum, sizeof(sum));
      exit(EXIT_SUCCESS);
    }
  }
  //Не создаем зомби, проверяем все процессы
  int status = 0;
  for (size_t i = 0; i < process; ++i) {
    wait(&status);
  }

  //считываем из всех пайпов результат
  for (size_t i = 0; i < process; ++i) {
    int sum = 0;
    read(pipes->fd[i][0], &sum, sizeof(int));
    *result += sum;
  }

  //освобождение памяти
  if (free_pipes(pipes)) {
    return -1;
  }
  return 0;
}