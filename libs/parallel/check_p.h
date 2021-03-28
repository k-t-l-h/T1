#ifndef T1_CHECK_P_H
#define T1_CHECK_P_H

#include <stdio.h>

typedef struct {
  int** fd;     //массив fd[2]
  size_t size;  //сколько процессов у нас есть
} pipes_t;

int check_p(int (*)(int), int*, size_t, int*);
pipes_t* create(size_t);
int free_pipes(pipes_t*);

#endif  // T1_CHECK_P_H
