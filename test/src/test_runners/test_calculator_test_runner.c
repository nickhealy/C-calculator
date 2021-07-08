#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(Calculator) {
  // RUN_TEST_CASE(Calculator, does_simple_calculations);
  // RUN_TEST_CASE(Calculator, does_complex_calculations);
  RUN_TEST_CASE(Calculator, split_args_splits_input_simple);
}