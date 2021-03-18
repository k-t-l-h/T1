#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "toy.h"

//дополнительная функция освобождения массива информации
void free_toys(Toy* toy) {
    if (NULL != toy) {
        free(toy);
    }
}

//дополнительная функция печати информации об игрушке
void print_toy(Toy* toy) {
    if (NULL == toy) {
        return;
    }

    printf("Toy name: %s\n", toy->Name);
    printf("Price: %.2f\n", toy->Price);  //округляем до копеек
    printf("Avaliable: %Iu\n", toy->Avaliable);
    printf("Country: %s\n", toy->Country);
}

//дополнительная функция загрузки массива информации из файла
Toy* read_all_toys(FILE* fp, ssize_t * toys_num) {
    if (fp == NULL) {
        printf("File cannot be opened\n");
        return NULL;
    }

    if (fscanf(fp, "%Iu", toys_num) != 1) {
        printf("Incorrect data format\n");
        return NULL;
    }

    //не аллоцируем нулевую память
    if (*toys_num <= 0) {
        printf("No toys to be found\n");
        return NULL;
    }

    Toy* toys = (Toy*)calloc(*toys_num, sizeof(Toy));

    if (NULL == toys) {
        printf("Allocation problem\n");
        return NULL;
    }

    for (int i = 0; i < *toys_num; i++) {
        // EILSEQ, EINVAL and other check
        // SHOULD specify a field width for the "%s" string placeholder
        if (1 != fscanf(fp, "%31s", toys[i].Name)) {
            printf("Incorrect input in name field\n");
            free_toys(toys);
            return NULL;
        }
        if (1 != fscanf(fp, "%f", &toys[i].Price)) {
            printf("Incorrect input in price field\n");
            free_toys(toys);
            return NULL;
        }
        if (1 != fscanf(fp, "%Iu", &toys[i].Avaliable)) {
            printf("Incorrect input in avaliable num field\n");
            free_toys(toys);
            return NULL;
        }
        if (1 != fscanf(fp, "%31s", toys[i].Country)) {
            printf("Incorrect input in country field \n");
            free_toys(toys);
            return NULL;
        }
    }

    return toys;
}

//функция поиска количества игрушек
int find_toys(Toy* toys, ssize_t toys_size, const char* country) {
    if (NULL == toys || NULL == country) {
        printf("Null data passed\n");
        return -1;
    }

    int num = 0;
    for (int i = 0; i < toys_size; i++) {
        if (strcmp(toys[i].Country, country) == 0) {
            print_toy(&toys[i]);
            num++;
        }
    }

    return num;
}
