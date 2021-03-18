/*
Создать структуру для хранения позиций каталога магазина детских игрушек:
названия и стоимости каждой игрушки, объема складских запасов,
а также страны-производителя.
Составить с ее использованием программу определения наличия игрушек,
произведенных в интересующей пользователя стране.
*/

#include <stdio.h>
#include "toy.h"

#define ARGERROR -1
#define FILEERROR -2

int main(int argc, char** argv) {
    //ошибка: файл с датой не передан или не передано название
    if (argc < 3) {
        printf("Not enough arguments\n");
        return ARGERROR;
    }

    FILE* fp = NULL;
    if ((fp = fopen(argv[1], "r")) == NULL) {
        printf("Can't open specified file\n");
        return FILEERROR;
    }

    ssize_t toy_num = 0;
    Toy* toys = read_all_toys(fp, &toy_num);
    int found = 0;
    found = find_toys(toys, toy_num, argv[2]);
    if (found > 0) {
        printf("Toys found :%d\n", found);
    } else {
        printf("Found no toys\n");
    }
    free_toys(toys);
    fclose(fp);

    return 0;
}