/*
Создать структуру для хранения позиций каталога магазина детских игрушек:
названия и стоимости каждой игрушки, объема складских запасов,
а также страны-производителя.
Составить с ее использованием программу определения наличия игрушек,
произведенных в интересующей пользователя стране.
*/

#include <stdio.h>
#include <string.h>

#define SIZE 32

typedef struct {
    char Name[SIZE];
    float Price;
    unsigned int Avaliable;
    char Country[SIZE];
} Toy;

int main(int argc, char** argv)
{
    //ошибка: файл с датой не передан или не передано название
    if (argc < 3) {
        printf("Not enough arguments\n");
        return 0;
    }

    FILE* fp;
    if ((fp = fopen(argv[1], "r")) == NULL) {
        printf("Can't open specified file\n");
        return 0;
    }

    int n = 0;
    int check = 0;

    check = fscanf(fp, "%d", &n);
    if (check != 1 )
        {
            printf("Incorrect data format\n");
            return 0;
        }




    for (int i = 0; i < n; i++) {
        Toy toy;
        //TODO: обработка ошибок чтения
        fscanf(fp, "%s", &toy.Name);
        fscanf(fp, "%f", &toy.Price);
        fscanf(fp, "%f", &toy.Avaliable);
        fscanf(fp, "%s", &toy.Country);

        if (strcmp(toy.Country, argv[2]) == 0) {
            printf("Name: %s\n", toy.Name);
            printf("Price: %f\n", toy.Price);
            printf("Avaliable: %d\n", toy.Avaliable);
            printf("Country: %s\n", toy.Country);
        }
    }

    //Не забываем закрыть файл
    fclose(fp);
    return 0;
}