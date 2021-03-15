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
void find_toy_by_country(FILE*, const char*);

#endif  // T1_TOY_H
