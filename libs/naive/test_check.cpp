#include <gtest/gtest.h>

extern "C" {
    #include "check.h"
}

int predicate(int a) {
    return 1;
}

//не передан предикат
TEST(TEST_CHECK, no_predicate) {
    size_t num = 0;
    num = check(nullptr, nullptr, 0);
    ASSERT_EQ(num, 0);
}

//не передан массив
TEST(TEST_CHECK, no_array) {
    size_t num = 0;
    num = check(predicate, nullptr, 0);
    ASSERT_EQ(num, 0);
}

//не передан массив
TEST(TEST_CHECK, all_good) {
    int arr[5] = {};
    size_t num = 5;
    num = check(predicate, arr, num);
    ASSERT_EQ(num, num);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}