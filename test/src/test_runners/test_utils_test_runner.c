#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(Utils) {
  RUN_TEST_CASE(Utils, is_num_input_positive);
  RUN_TEST_CASE(Utils, is_num_input_negative);
  RUN_TEST_CASE(Utils, is_num_input_non_num);
}