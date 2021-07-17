#include "unity_fixture.h"

static void RunAllTests(void) {
  RUN_TEST_GROUP(ToPostfix);
  RUN_TEST_GROUP(EvalPostfix);
  RUN_TEST_GROUP(Calculator);
  RUN_TEST_GROUP(isValidToken);
  RUN_TEST_GROUP(Utils);
}

int main(int argc, const char* argv[]) {
  return UnityMain(argc, argv, RunAllTests);
}