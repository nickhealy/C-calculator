#include <stdio.h>
#include <stdlib.h>

#include "../src/toPostfix.h"
#include "vendor/unity.h"

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_convert_addition(void) {
  char *infix[] = {"40", "+", "7"};
  char *postfix[] = {"40", "7", "+"};
  char **result = to_postfix(infix, 3);
  TEST_ASSERT_EQUAL_STRING_ARRAY(postfix, result, 3);
  free(result);
}
void test_convert_addition_subtraction(void) {
  char *infix[] = {"4", "+", "70", "-", "3"};
  char *postfix[] = {"4", "70", "+", "3", "-"};
  char **result = to_postfix(infix, 5);
  TEST_ASSERT_EQUAL_STRING_ARRAY(postfix, result, 5);
  free(result);
}
void test_convert_with_multiplication(void) {
  char *infix[] = {"2", "+", "4", "*", "71", "-", "2"};
  char *postfix[] = {"2", "4", "71", "*", "+", "2", "-"};
  char **result = to_postfix(infix, 7);
  TEST_ASSERT_EQUAL_STRING_ARRAY(postfix, result, 7);
  free(result);
}
void test_convert_with_multi_and_divide(void) {
  char *infix[] = {"4", "+", "7"};
  char *postfix[] = {"4", "7", "+"};
  char **result = to_postfix(infix, 3);
  TEST_ASSERT_EQUAL_STRING_ARRAY(postfix, result, 3);
  free(result);
}
void test_convert_combined(void) {
  char *infix[] = {"4", "/", "2", "-", "1", "+", "3", "/", "2", "*", "6"};
  char *postfix[] = {"4", "2", "/", "1", "-", "3", "2", "/", "6", "*", "+"};
  char **result = to_postfix(infix, 11);
  TEST_ASSERT_EQUAL_STRING_ARRAY(postfix, result, 11);
  free(result);
}

void test_convert_parens_simple(void) {
  char *infix[] = {"(", "3", "-", "1", ")", "*", "2"};
  char *postfix[] = {"3", "1", "-", "2"};
  char **result = to_postfix(infix, 7);
  TEST_ASSERT_EQUAL_STRING_ARRAY(postfix, result, 4);
  free(result);
}

void test_convert_parens_complex(void) {
  char *infix[] = {"(", "(", "3", "-", "1", ")", "*", "2",
                   ")", "/", "3", "^", "2", "+", "5"};
  char *postfix[] = {"3", "1", "-", "2", "*", "3", "2", "^", "/", "5", "+"};
  char **result = to_postfix(infix, 15);
  TEST_ASSERT_EQUAL_STRING_ARRAY(postfix, result, 11);
  free(result);
}

void test_mixed(void) {
  char *infix[] = {"3", "+", "4", "*", "2", "/", "(", "1",
                   "-", "5", ")", "^", "2", "^", "3"};
  char *postfix[] = {"3", "4", "2", "*", "1", "5", "-",
                     "2", "3", "^", "^", "/", "+"};
  char **result = to_postfix(infix, 15);
  TEST_ASSERT_EQUAL_STRING_ARRAY(postfix, result, 13);
  free(result);
}

void test_incomplete_parens_left(void) {
  char *infix[] = {"(", "2", "+", "3"};
  TEST_ASSERT_EQUAL(NULL, to_postfix(infix, 4));
}

void test_incomplete_parens_right(void) {
  char *infix[] = {"2", "+", "3", ")"};
  TEST_ASSERT_EQUAL(NULL, to_postfix(infix, 4));
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_convert_addition);
  RUN_TEST(test_convert_addition_subtraction);
  RUN_TEST(test_convert_with_multiplication);
  RUN_TEST(test_convert_with_multi_and_divide);
  RUN_TEST(test_convert_combined);
  RUN_TEST(test_convert_parens_simple);
  RUN_TEST(test_convert_parens_complex);
  RUN_TEST(test_mixed);
  RUN_TEST(test_incomplete_parens_left);
  RUN_TEST(test_incomplete_parens_right);
  return UNITY_END();
}
