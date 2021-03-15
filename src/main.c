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

    find_toy_by_country(fp, argv[2]);
    fclose(fp);

    return 0;
}