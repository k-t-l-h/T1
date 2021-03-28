#include <gtest/gtest.h>

extern "C" {
    #include "check.h"
}

int predicate(int a) {
    return 1;
}

//не передан предикат
TEST(TEST_CHECK, no_predicate) {
    int code = 0;
    size_t result = 0;
    code = check(nullptr, nullptr, 0, &result);
    ASSERT_EQ(code, -1);
}

//не передан массив
TEST(TEST_CHECK, no_array) {
    int code = 0;
    size_t result = 0;
    code = check(nullptr, nullptr, 0, &result);
    ASSERT_EQ(code, -1);
}

//передан массив
TEST(TEST_CHECK, all_good) {
    int arr[5] = {};
    size_t num = 5;
    size_t result = 0;
    int code  = check(predicate, arr, num, &result);
    ASSERT_EQ(code, 0);
    ASSERT_EQ(result, num);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}