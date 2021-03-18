#include <gtest/gtest.h>

extern "C" {
#include "toy.h"
}

//Тесты на корректную загрузку из файла
TEST(TEST_TOY, read_toys){
    FILE* fp = NULL;
    fp = fopen(argv[1], "r"));

    fclose(fp);
}

//Тесты на корректый поиск количества
//Тесты на печать?
//Тесты на освобождение памяти


int main(int argc, char** argv) {

    Toy toy = {
            "Name",
            2.15,
            2,
            "Moscow"
    };

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}