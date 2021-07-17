#include <stdio.h>
#include <stdlib.h>

#include "unity.h"
#include "unity_fixture.h"
#include "utils.h"

TEST_GROUP(Utils);

TEST_SETUP(Utils) {
  // set stuff up here
}

TEST_TEAR_DOWN(Utils) {
  // tear stuff down here
}

TEST(Utils, is_num_input_positive) {
  TEST_ASSERT_TRUE(is_num("1"));
  TEST_ASSERT_TRUE(is_num("15"));
  TEST_ASSERT_TRUE(is_num("1.5"));
  TEST_ASSERT_TRUE(is_num("15.5"));
  TEST_ASSERT_TRUE(is_num("0.5"));
  TEST_ASSERT_TRUE(is_num(".5"));
}

TEST(Utils, is_num_input_negative) {
  TEST_ASSERT_TRUE(is_num("-1"));
  TEST_ASSERT_TRUE(is_num("-15"));
  TEST_ASSERT_TRUE(is_num("-1.5"));
  TEST_ASSERT_TRUE(is_num("-15.5"));
  TEST_ASSERT_TRUE(is_num("-0.5"));
  TEST_ASSERT_TRUE(is_num("-.5"));
}

TEST(Utils, is_num_input_non_num) {
  TEST_ASSERT_FALSE(is_num("+"));
  TEST_ASSERT_FALSE(is_num("-"));
  TEST_ASSERT_FALSE(is_num("."));
  TEST_ASSERT_FALSE(is_num("/"));
}