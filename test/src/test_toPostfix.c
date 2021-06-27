#include <stdio.h>
#include <stdlib.h>

#include "toPostfix.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(ToPostfix);

TEST_SETUP(ToPostfix) {
  // set stuff up here
}

TEST_TEAR_DOWN(ToPostfix) {
  // tear stuff down here
}

void test_convert_addition(void);
void test_convert_addition_subtraction(void);
void test_convert_with_multiplication(void);
void test_convert_with_multi_and_divide(void);
void test_convert_combined(void);
void test_convert_parens_simple(void);
void test_convert_parens_complex(void);
void test_mixed(void);

void test_incomplete_parens_left(void);
void test_incomplete_parens_right(void);

void test_convert_addition(void) {
  const char *infix[] = {"40", "+", "7"};
  const char *postfix[] = {"40", "7", "+", NULL};
  const char **result = to_postfix(infix, 3);
  TEST_ASSERT_EQUAL_STRING_ARRAY(postfix, result, 4);
  free(result);
}

void test_convert_addition_subtraction(void) {
  const char *infix[] = {"4", "+", "70", "-", "3"};
  const char *postfix[] = {"4", "70", "+", "3", "-", NULL};
  const char **result = to_postfix(infix, 5);
  TEST_ASSERT_EQUAL_STRING_ARRAY(postfix, result, 6);
  free(result);
}

void test_convert_with_multiplication(void) {
  const char *infix[] = {"2", "+", "4", "*", "71", "-", "2"};
  const char *postfix[] = {"2", "4", "71", "*", "+", "2", "-", NULL};
  const char **result = to_postfix(infix, 7);
  TEST_ASSERT_EQUAL_STRING_ARRAY(postfix, result, 8);
  free(result);
}

void test_convert_with_multi_and_divide(void) {
  const char *infix[] = {"4", "+", "7"};
  const char *postfix[] = {"4", "7", "+", NULL};
  const char **result = to_postfix(infix, 3);
  TEST_ASSERT_EQUAL_STRING_ARRAY(postfix, result, 4);
  free(result);
}

void test_convert_combined(void) {
  const char *infix[] = {"4", "/", "2", "-", "1", "+", "3", "/", "2", "*", "6"};
  const char *postfix[] = {"4", "2", "/", "1", "-", "3",
                           "2", "/", "6", "*", "+", NULL};
  const char **result = to_postfix(infix, 11);
  TEST_ASSERT_EQUAL_STRING_ARRAY(postfix, result, 12);
  free(result);
}

void test_convert_parens_simple(void) {
  const char *infix[] = {"(", "3", "-", "1", ")", "*", "2"};
  const char *postfix[] = {"3", "1", "-", "2", "*", NULL};
  const char **result = to_postfix(infix, 7);
  TEST_ASSERT_EQUAL_STRING_ARRAY(postfix, result, 6);
  free(result);
}

void test_convert_parens_complex(void) {
  const char *infix[] = {"(", "(", "3", "-", "1", ")", "*", "2",
                         ")", "/", "3", "^", "2", "+", "5"};
  const char *postfix[] = {"3", "1", "-", "2", "*", "3",
                           "2", "^", "/", "5", "+", NULL};
  const char **result = to_postfix(infix, 15);
  TEST_ASSERT_EQUAL_STRING_ARRAY(postfix, result, 12);
  free(result);
}

void test_mixed(void) {
  const char *infix[] = {"3", "+", "4", "*", "2", "/", "(", "1",
                         "-", "5", ")", "^", "2", "^", "3"};
  const char *postfix[] = {"3", "4", "2", "*", "1", "5", "-",
                           "2", "3", "^", "^", "/", "+", NULL};
  const char **result = to_postfix(infix, 15);
  TEST_ASSERT_EQUAL_STRING_ARRAY(postfix, result, 14);
  free(result);
}

void test_incomplete_parens_left(void) {
  const char *infix[] = {"(", "2", "+", "3"};
  TEST_ASSERT_EQUAL(NULL, to_postfix(infix, 4));
}

void test_incomplete_parens_right(void) {
  const char *infix[] = {"2", "+", "3", ")"};
  TEST_ASSERT_EQUAL(NULL, to_postfix(infix, 4));
}

TEST(ToPostfix, to_postfix_tests) {
  test_convert_addition();
  test_convert_addition_subtraction();
  test_convert_with_multiplication();
  test_convert_with_multi_and_divide();
  test_convert_combined();
  test_convert_parens_simple();
  test_convert_parens_complex();
  test_mixed();
}

TEST(ToPostfix, to_postfix_error_cases) {
  test_incomplete_parens_left();
  test_incomplete_parens_right();
}