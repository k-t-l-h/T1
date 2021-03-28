//Здесь работа с каналами

#include <stdlib.h>
#include <unistd.h>
#include "check_p.h"

pipes_t *create(size_t size) {
  //память под саму структуру
  pipes_t *pipes = (pipes_t *)malloc(sizeof(pipes_t));
  if (pipes == NULL) {
    return NULL;
  }
  //передаем число процессов
  pipes->size = size;

  //память под дескрипторы
  pipes->fd = (int *)malloc(size * sizeof(int *));
  if (pipes->fd == NULL) {
    free(pipes);
    return NULL;
  }

  for (size_t i = 0; i < size; ++i) {
    //готовим массив
    pipes->fd[i] = (int *)malloc(2 * sizeof(int *));
    if (pipes->fd[i] == NULL) {
      // TODO: обработать ошибки
    }
    //пытаемся заполнить новыми дескрипторами
    if (pipe(pipes->fd[i]) != 0) {
      // TODO: обработать ошибки
    }
  }

  return pipes;
}

int free_pipes(pipes_t *pipes) {
  if (NULL == pipes) {
    return -1;
  }
  for (size_t i = 0; i < pipes->size; ++i) {
    close(pipes->fd[i][0]);
    close(pipes->fd[i][1]);
    free(pipes->fd[i]);
  }
  free(pipes->fd);
  free(pipes);
  return 0;
}