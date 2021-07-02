#include <stdio.h>
#include <stdlib.h>

#include "calculator.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Calculator);

TEST_SETUP(Calculator) {
  // set stuff up here
}

TEST_TEAR_DOWN(Calculator) {
  // tear stuff down here
}

TEST(Calculator, does_simple_calculations) {
  const char *expr_1[3] = {"1", "+", "0.5"};
  const char *expr_2[3] = {"2", "-", "1"};
  const char *expr_3[3] = {"2", "*", "3"};
  const char *expr_4[3] = {"2", "^", "3"};

  TEST_ASSERT_EQUAL_FLOAT(1.50, calculate(expr_1, 3));
  TEST_ASSERT_EQUAL_FLOAT(1.00, calculate(expr_2, 3));
  TEST_ASSERT_EQUAL_FLOAT(6.00, calculate(expr_3, 3));
  TEST_ASSERT_EQUAL_FLOAT(8.00, calculate(expr_4, 3));
}

TEST(Calculator, does_complex_calculations) {
  const char *expr_1[7] = {"(", "1", "+", "3", ")", "*", "2"};
  const char *expr_2[11] = {"(", "3", "*", "(", "1", "+",
                            "3", ")", ")", "*", "2"};
  const char *expr_3[11] = {"(", "(", "3", "+", "2", ")",
                            "^", "2", ")", "/", "2"};

  TEST_ASSERT_EQUAL_FLOAT(8.00, calculate(expr_1, 7));
  TEST_ASSERT_EQUAL_FLOAT(24.00, calculate(expr_2, 11));
  TEST_ASSERT_EQUAL_FLOAT(12.5, calculate(expr_3, 11));
}