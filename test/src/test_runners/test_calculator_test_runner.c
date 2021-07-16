#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(Calculator) {
  RUN_TEST_CASE(Calculator, does_simple_calculations);
  RUN_TEST_CASE(Calculator, does_complex_calculations);
  // if you switch the order of these bottom two, one of the tests breaks for
  // some reason....
  RUN_TEST_CASE(Calculator, split_args_splits_input_complex);
  RUN_TEST_CASE(Calculator, split_args_splits_input_simple);
}