//Здесь работа с каналами

#include <stdlib.h>
#include <unistd.h>
#include "check_p.h"

pipes_t *create_pipes(size_t size) {
  //не создаем пустые структуры
  if (size <= 0) {
    return NULL;
  }

  //память под саму структуру
  pipes_t *pipes = (pipes_t *)malloc(sizeof(pipes_t));
  if (pipes == NULL) {
    return NULL;
  }
  //передаем число процессов
  pipes->size = size;

  //память под дескрипторы
  pipes->fd = (int**)malloc(size * sizeof(int*));
  if (pipes->fd == NULL) {
    free(pipes);
    return NULL;
  }

  for (size_t i = 0; i < size; ++i) {
    //готовим массив
    pipes->fd[i] = (int *)malloc(2 * sizeof(int));
    if (pipes->fd[i] == NULL) {
      //закрываем все что успели открыть
      free_pipes(pipes);
      return NULL;
    }
    //пытаемся заполнить новыми дескрипторами
    if (pipe(pipes->fd[i]) != 0) {
      free_pipes(pipes);
      return NULL;
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

int write_pipe(pipes_t *pipes, size_t pipe_index, int value) {
  if (NULL == pipes) {
    return -1;
  }

  if (pipe_index >= pipes->size) {
    return -1;
  }

  if (write(pipes->fd[pipe_index][1], &value, sizeof(value)) == -1) {
    return -1;
  }
  return 0;
}