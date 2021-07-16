#include <stdio.h>
#include <stdlib.h>

#include "split_args.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(isValidToken);

TEST_SETUP(isValidToken) {  // set stuff up here
}

TEST_TEAR_DOWN(isValidToken) {
  // tear stuff down here
}

TEST(isValidToken, leading_operators_no_neg) {
  TEST_ASSERT_FALSE(is_valid_token("-", '.', false));
  TEST_ASSERT_FALSE(is_valid_token("-", '2', false));
  TEST_ASSERT_FALSE(is_valid_token("-", '-', false));
  TEST_ASSERT_FALSE(is_valid_token("+", '+', false));
  TEST_ASSERT_FALSE(is_valid_token("+", '(', false));
}

TEST(isValidToken, leading_operators_with_neg) {
  TEST_ASSERT_TRUE(is_valid_token("-", '.', true));
  TEST_ASSERT_TRUE(is_valid_token("-", '2', true));
  TEST_ASSERT_FALSE(is_valid_token("-", '-', true));
  TEST_ASSERT_TRUE(is_valid_token("-22", '2', true));
  TEST_ASSERT_FALSE(is_valid_token("-22", '+', true));
}

TEST(isValidToken, leading_number) {
  TEST_ASSERT_TRUE(is_valid_token("2", '2', false));
  TEST_ASSERT_TRUE(is_valid_token("2.", '2', false));
  TEST_ASSERT_FALSE(is_valid_token("2.", '.', false));
  TEST_ASSERT_TRUE(is_valid_token("2", '.', false));
  TEST_ASSERT_FALSE(is_valid_token("2", '-', false));
  TEST_ASSERT_FALSE(is_valid_token("2", '(', false));
}

TEST(isValidToken, leading_point) {
  TEST_ASSERT_TRUE(is_valid_token(".", '2', false));
  TEST_ASSERT_FALSE(is_valid_token(".", '.', false));
  TEST_ASSERT_FALSE(is_valid_token("2", '-', false));
  TEST_ASSERT_FALSE(is_valid_token("2", '(', false));
}

TEST(isValidToken, leading_parens) {
  TEST_ASSERT_FALSE(is_valid_token("(", '2', false));
  TEST_ASSERT_FALSE(is_valid_token("(", '.', false));
  TEST_ASSERT_FALSE(is_valid_token("(", '-', false));
  TEST_ASSERT_FALSE(is_valid_token("(", '(', false));
}