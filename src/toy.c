#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "toy.h"

void free_toys(Toy* toy) {
    if (NULL != toy) {
        free(toy);
    }
}

Toy* read_all_toys(FILE* fp, size_t* toys_num) {
    if (fscanf(fp, "%Iu", toys_num) != 1) {
        printf("Incorrect data format\n");
        return NULL;
    }

    //не аллоцируем нулевую память
    if (*toys_num == 0) {
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

void find_toy_by_country(FILE* fp, const char* country) {
    if (NULL == fp || NULL == country) {
        printf("Null data passed\n");
        return;
    }

    size_t toys_num;
    toys_num = 0;
    Toy* toys = read_all_toys(fp, &toys_num);
    if (NULL != toys) {
        for (int i = 0; i < toys_num; ++i) {
            if (strcmp(toys[i].Country, country) == 0) {
                printf("Name: %s\n", toys[i].Name);
                printf("Price: %f\n", toys[i].Price);
                printf("Avaliable: %Iu\n", toys[i].Avaliable);
                printf("Country: %s\n", toys[i].Country);
            }
        }
        free_toys(toys);
    }
}