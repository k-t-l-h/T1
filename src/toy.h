#ifndef T1_TOY_H
#define T1_TOY_H

#define SIZE 32

typedef struct {
    char Name[SIZE];
    float Price;
    ssize_t Avaliable;
    char Country[SIZE];
} Toy;

void free_toys(Toy*);
void print_toy(Toy*);
Toy* read_all_toys(FILE*, size_t *);
int find_toys(Toy*, size_t, const char*);

#endif  // T1_TOY_H
