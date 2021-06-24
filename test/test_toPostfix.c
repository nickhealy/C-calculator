#include "vendor/unity.h"
#include "../src/toPostfix.h"

#include <stdio.h>

void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}

void test_convert_addition(void)
{
  char *infix[] = {"40", "+", "7"};
  char *postfix[] = {"40", "7", "+"};
  TEST_ASSERT_EQUAL_STRING_ARRAY(postfix, to_postfix(infix, 3), 3);
}
void test_convert_addition_subtraction(void)
{
  char *infix[] = {"4", "+", "70", "-", "3"};
  char *postfix[] = {"4", "70", "+", "3", "-"};
  TEST_ASSERT_EQUAL_STRING_ARRAY(postfix, to_postfix(infix, 5), 5);
}
void test_convert_with_multiplication(void)
{
  TEST_IGNORE();
  char *infix[] = {"2", "+", "4", "*", "71", "-", "2"};
  char *postfix[] = {"2", "4", "71", "*", "+", "2", "-"};
  TEST_ASSERT_EQUAL_STRING_ARRAY(postfix, to_postfix(infix, 7), 7);
}
void test_convert_with_multi_and_divide(void)
{
  TEST_IGNORE();
  char *infix[] = {"4", "+", "7"};
  char *postfix[] = {"4", "7", "+"};
  TEST_ASSERT_EQUAL_STRING_ARRAY(postfix, to_postfix(infix, 3), 3);
}
void test_convert_combined(void)
{
  TEST_IGNORE();
  char *infix[] = {"4", "/", "2", "-", "1", "+", "3", "/", "2", "*", "6"};
  char *postfix[] = {"4", "2", "/", "1", "-", "3", "2", "/", "6", "*", "+"};
  TEST_ASSERT_EQUAL_STRING_ARRAY(postfix, to_postfix(infix, 11), 11);
}

void test_convert_parens_simple(void)
{
  TEST_IGNORE();
  char *infix[] = {"(", "3", "-", "1", ")", "*", "2"};
  char *postfix[] = {"3", "1", "-", "2"};
  TEST_ASSERT_EQUAL_STRING_ARRAY(postfix, to_postfix(infix, 7), 4);
}

void test_convert_parens_complex(void)
{
  TEST_IGNORE();
  char *infix[] = {"(", "(", "3", "-", "1", ")", "*", "2", ")", "/", "3", "^", "2", "+", "5"};
  char *postfix[] = {"3", "1", "-", "2", "*", "3", "2", "^", "/", "5", "+"};
  TEST_ASSERT_EQUAL_STRING_ARRAY(postfix, to_postfix(infix, 15), 11);
}

void test_mixed(void)
{
  TEST_IGNORE();
  char *infix[] = {"3", "+", "4", "*", "2", "/", "(", "1", "−", "5", ")", "^", "2", "^", "3"};
  char *postfix[] = {"3", "4", "2", "*", "1", "5", "−", "2", "3", "^", "^", "/", "/"};
  TEST_ASSERT_EQUAL_STRING_ARRAY(postfix, to_postfix(infix, 15), 13);
}

void test_incomplete_parens(void)
{
  TEST_IGNORE();
  char *infix[] = {"(", "2", "+", "3"};
  TEST_ASSERT_EQUAL(NULL, to_postfix(infix, 4));
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_convert_addition);
  RUN_TEST(test_convert_addition_subtraction);
  RUN_TEST(test_convert_with_multiplication);
  RUN_TEST(test_convert_with_multi_and_divide);
  RUN_TEST(test_convert_combined);
  RUN_TEST(test_convert_parens_simple);
  RUN_TEST(test_convert_parens_complex);
  RUN_TEST(test_mixed);
  RUN_TEST(test_incomplete_parens);
  return UNITY_END();
}
