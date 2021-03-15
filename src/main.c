/*
Создать структуру для хранения позиций каталога магазина детских игрушек:
названия и стоимости каждой игрушки, объема складских запасов,
а также страны-производителя.
Составить с ее использованием программу определения наличия игрушек,
произведенных в интересующей пользователя стране.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 32

typedef struct {
    char Name[SIZE];
    float Price;
    unsigned int Avaliable;
    char Country[SIZE];
} Toy;

int main(int argc, char** argv) {
    //ошибка: файл с датой не передан или не передано название
    if (argc < 3) {
        printf("Not enough arguments\n");
        return 0;
    }

    FILE* fp = NULL;
    if ((fp = fopen(argv[1], "r")) == NULL) {
        printf("Can't open specified file\n");
        return 0;
    }

    int n = 0;
    int check = 0;

    check = fscanf(fp, "%d", &n);
    if (1 != check) {
        printf("Incorrect data format\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {

        Toy *toy = (Toy*)malloc(sizeof(Toy));
        if (NULL == toy) {
            printf("Allocation problem\n");
            return 0;
        }

        //EILSEQ, EINVAL and other check
        //SHOULD specify a field width for the "%s" string placeholder
        if (1 != fscanf(fp, "%31s", toy->Name)) {
            printf("Incorrect input in name field \n");
            free(toy);
            return 0;
        }
        if (1 != fscanf(fp, "%f", &toy->Price)) {
            printf("Incorrect input in price field \n");
            free(toy);
            return 0;
        }
        if (1 !=  fscanf(fp, "%u", &toy->Avaliable)) {
            printf("Incorrect input in avaliable num field \n");
            free(toy);
            return 0;
        }
        if (1 != fscanf(fp, "%31s", toy->Country)) {
            printf("Incorrect input in country field \n");
            free(toy);
            return 0;
        }

        if (strcmp(toy->Country, argv[2]) == 0) {
            printf("Name: %s\n", toy->Name);
            printf("Price: %f\n", toy->Price);
            printf("Avaliable: %u\n", toy->Avaliable);
            printf("Country: %s\n", toy->Country);
        }

        free(toy);
    }

    //Не забываем закрыть файл
    fclose(fp);
    return 0;
}