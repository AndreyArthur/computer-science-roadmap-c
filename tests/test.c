#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct TestRunner {
  void(*it)(char *message, int(*callback)());
  void(*end)(struct TestRunner *test);
};

void _test_runner_it(char *message, int(*callback)()) {
  char result_text[5];
  int result = callback();
  if (result == 1) {
    stpcpy(result_text, "OK");
  } else {
    stpcpy(result_text, "FAIL");
  }
  printf("  It %s: %s\n", message, result_text);
}

void _test_runner_end(struct TestRunner *test) {
  free(test);
}

struct TestRunner *describe(char *testing) {
  printf("Testing: %s\n", testing);
  struct TestRunner *test = (struct TestRunner *)malloc(
    sizeof(struct TestRunner)
  );
  test->it = &_test_runner_it;
  test->end = &_test_runner_end;
  return test;
}

