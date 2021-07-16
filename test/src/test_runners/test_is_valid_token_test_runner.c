#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(isValidToken) {
  RUN_TEST_CASE(isValidToken, leading_operators_no_neg);
  RUN_TEST_CASE(isValidToken, leading_operators_with_neg);
  RUN_TEST_CASE(isValidToken, leading_number);
  RUN_TEST_CASE(isValidToken, leading_point);
  RUN_TEST_CASE(isValidToken, leading_parens);
}