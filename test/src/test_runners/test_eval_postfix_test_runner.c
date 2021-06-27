#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(EvalPostfix) {
  RUN_TEST_CASE(EvalPostfix, evals_simple_expressions);
  RUN_TEST_CASE(EvalPostfix, evals_complex_expressions);
}