#include <gtest/gtest.h>

extern "C" {
    #include "check_p.h"
}

int predicate(int a) {
    return 1;
}

int second_predicate(int a) {
  return a % 13 == 4;
}


//Стандартные тесты на главную функцию

//не передан предикат
TEST(TEST_CHECK_P, no_predicate) {
    int code = 0;
    size_t result = 0;
    code = check_p(nullptr, nullptr, 0, &result);
    ASSERT_EQ(code, -1);
}

//не передан массив
TEST(TEST_CHECK_P, no_array) {
    int code = 0;
    size_t result = 0;
    code = check_p(nullptr, nullptr, 0, &result);
    ASSERT_EQ(code, -1);
}

//передан массив
TEST(TEST_CHECK_P, all_good) {
    int arr[5] = {};
    size_t num = 5;
    size_t result = 0;
    int code  = check_p(predicate, arr, num, &result);
    ASSERT_EQ(code, 0);
    ASSERT_EQ(result, num);
}

//Тесты на вторую функцию
//не передан предикат
TEST(TEST_CHECK_P_P, no_predicate) {
  int code = 0;
  size_t result = 0;
  code = check_predicate_range(nullptr, nullptr, 0, 0, &result);
  ASSERT_EQ(code, -1);
}

//не передан массив
TEST(TEST_CHECK_P_P, no_array) {
  int code = 0;
  size_t result = 0;
  code = check_predicate_range(nullptr, nullptr, 0, 0, &result);
  ASSERT_EQ(code, -1);
}

//передан массив
TEST(TEST_CHECK_P_P, all_good) {
  int arr[5] = {};
  size_t num = 5;
  size_t result = 0;
  int code  = check_predicate_range(predicate, arr, 0, num, &result);
  ASSERT_EQ(code, 0);
  ASSERT_EQ(result, num);
}

//передан массив + второй предикат
TEST(TEST_CHECK_P_P, all_good_2) {
  int arr[10] = {
      -31261, -3194, 823, -4546, 14967,
      -31260, -3195, 824, -4548, 14962,
  };
  size_t num = 10;
  size_t result = 0;
  int code  = check_predicate_range(second_predicate, arr, 0, num, &result);
  ASSERT_EQ(code, 0);
  //суровая реальность с отрицательным результатом mod
  ASSERT_EQ(result, 2);
}


//Тесты на пайпы
TEST(TEST_CHECK_PIPES, create_pipes_bad_size) {
  pipes_t *pipes = nullptr;
  pipes = create_pipes(0);
  ASSERT_EQ(pipes, nullptr);
}

TEST(TEST_CHECK_PIPES, create_pipes_good_size) {
  pipes_t *pipes = nullptr;
  pipes = create_pipes(5);
  ASSERT_NE(pipes, nullptr);
  free_pipes(pipes);
}

TEST(TEST_CHECK_PIPES, delete_pipes_bad) {
  pipes_t *pipes = nullptr;
  int result = 0;
  result = free_pipes(pipes);
  ASSERT_EQ(result, -1);
}


TEST(TEST_CHECK_PIPES, delete_pipes_good) {
  pipes_t *pipes = nullptr;
  pipes = create_pipes(5);
  int result = 0;
  result = free_pipes(pipes);
  ASSERT_NE(result, -1);
}

TEST(TEST_CHECK_PIPES, write_pipe_all_good) {
  pipes_t *pipes = nullptr;
  pipes = create_pipes(5);
  int result = 0;
  result = write_pipe(pipes, 0, 1);
  ASSERT_NE(result, -1);
  free_pipes(pipes);
}

TEST(TEST_CHECK_PIPES, write_pipe_wrong_size) {
  pipes_t *pipes = nullptr;
  pipes = create_pipes(5);
  int result = 0;
  result = write_pipe(pipes, 10, 1);
  ASSERT_EQ(result, -1);
  free_pipes(pipes);
}

TEST(TEST_CHECK_PIPES, write_pipe_wrong_ptr) {
  pipes_t *pipes = nullptr;
  int result = 0;
  result = write_pipe(pipes, 1, 1);
  ASSERT_EQ(result, -1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}