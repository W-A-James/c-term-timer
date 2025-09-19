#ifndef TEST_COMMON_INCL
#define TEST_COMMON_INCL

#include <stdio.h>

#define RED(s) "\033[48;5;1m" s "\033[0m"
#define GREEN(s) "\033[48;5;2m" s "\033[0m"

#define START_SUITE(suite_name)                                                \
  int main() {                                                                 \
    int tests_passed = 0, tests_failed = 0, tests_total = 0;                   \
    printf("Test Suite ---- %s\n", (suite_name));

#define ASSERT_INT_EQUAL(actual, expected, name)                               \
  {                                                                            \
    printf("  %s -- ", (name));                                                \
    if ((actual) != (expected)) {                                              \
      puts(RED("Failed"));                                                     \
      printf("  Got " RED("%d"), (actual));                                    \
      printf(", Expected " GREEN("%d"), (expected));                           \
      puts("");                                                                \
      tests_failed++;                                                          \
    } else {                                                                   \
      puts(GREEN("Passed"));                                                   \
      puts("");                                                                \
      tests_passed++;                                                          \
    }                                                                          \
    tests_total++;                                                             \
  }

#define ASSERT_INT_BETWEEN(actual, expected, error, name)                      \
  {                                                                            \
    printf("  %s -- ", (name));                                                \
    if ((actual) > (expected + error) || (actual) < (expected - error)) {      \
      puts(RED("Failed"));                                                     \
      printf("  Got " RED("%d"), (actual));                                    \
      printf(", Expected " GREEN("%d +/- %d"), (expected), (error));           \
      puts("");                                                                \
      tests_failed++;                                                          \
    } else {                                                                   \
      puts(GREEN("Passed"));                                                   \
      puts("");                                                                \
      tests_passed++;                                                          \
    }                                                                          \
    tests_total++;                                                             \
  }

#define ASSERT_DOUBLE_BETWEEN(actual, expected, error, name)                   \
  {                                                                            \
    printf("  %s -- ", (name));                                                \
    if ((actual) > (expected + error) || (actual) < (expected - error)) {      \
      puts(RED("Failed"));                                                     \
      printf("  Got " RED("%f"), (actual));                                    \
      printf(", Expected " GREEN("%f +/- %f"), (expected), (error));           \
      puts("");                                                                \
      tests_failed++;                                                          \
    } else {                                                                   \
      puts(GREEN("Passed"));                                                   \
      puts("");                                                                \
      tests_passed++;                                                          \
    }                                                                          \
    tests_total++;                                                             \
  }

#define END_SUITE()                                                            \
  {                                                                            \
    printf("Tests Passed:\t%d\nTests Failed:\t%d\nTotal:\t%d\n", tests_passed, \
           tests_failed, tests_total);                                         \
                                                                               \
    if (tests_failed > 0)                                                      \
      return 1;                                                                \
    return 0;                                                                  \
  }                                                                            \
  }

#endif
