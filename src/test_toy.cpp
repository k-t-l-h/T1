#include <gtest/gtest.h>

extern "C" {
#include "toy.h"
}

//Тесты на корректную загрузку из файла
TEST(TEST_TOY, read_toys_good) {
    FILE* fp = nullptr;
    fp = fopen("data.txt", "r");
    ssize_t num = 0;
    Toy* toy = read_all_toys(fp, &num);
    ASSERT_NE(toy, nullptr);
    ASSERT_EQ(num, 1);
    fclose(fp);
}

TEST(TEST_TOY, read_toys_bad) {
    FILE* fp = nullptr;
    fp = fopen("incorrect_data.txt", "r");

    ssize_t num = 0;
    Toy* toy = read_all_toys(fp, &num);
    ASSERT_EQ(toy, nullptr);
    ASSERT_EQ(num, 0);

    fclose(fp);
}

TEST(TEST_TOY, read_toys_null) {
    FILE* fp = nullptr;

    ssize_t num = 0;
    Toy* toy = read_all_toys(fp, &num);
    ASSERT_EQ(toy, nullptr);
    ASSERT_EQ(num, 0);
}

//Тесты на корректый поиск количества

TEST(TEST_TOY, find_toys_bad) {
    Toy* toy = nullptr;
    ssize_t size = 0;
    int num = find_toys(toy, size, "");
    ASSERT_EQ(num, -1);
}

TEST(TEST_TOY, find_toys_good) {
    Toy toy = {"A", 2, 2, "B"};
    ssize_t size = 1;
    int num = find_toys(&toy, size, "B");
    ASSERT_EQ(num, 1);

    num = find_toys(&toy, size, "A");
    ASSERT_EQ(num, 0);
}

//Тесты на печать?
TEST(TEST_TOY, print_all_good) {
    Toy* toy_null = nullptr;
    ASSERT_NO_THROW(print_toy(toy_null));

    Toy toy = {"A", 2, 2, "B"};
    ASSERT_NO_THROW(print_toy(&toy));
}

//Тесты на освобождение памяти
TEST(TEST_TOY, free_all_good) {
    Toy* toy_null = nullptr;
    ASSERT_NO_THROW(free_toys(toy_null));

    Toy* toy = (Toy*)calloc(1, sizeof(Toy));
    ASSERT_NO_THROW(free_toys(toy));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}