#include <gtest/gtest.h>

extern "C" {
    #include "check.h"
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
    num = check([](int l) {return true;}, nullptr, 0);
    ASSERT_EQ(num, 0);
}

//не передан массив
TEST(TEST_CHECK, all_good) {
    int[] arr = [1, 2, 3, 4];
    size_t num = 0;
    num = check([](int l) {return true;}, nullptr, 4);
    ASSERT_EQ(num, 4);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}