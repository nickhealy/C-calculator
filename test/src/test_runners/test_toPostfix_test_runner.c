#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(ToPostfix) {
  RUN_TEST_CASE(ToPostfix, to_postfix_tests);
  RUN_TEST_CASE(ToPostfix, to_postfix_error_cases);
}