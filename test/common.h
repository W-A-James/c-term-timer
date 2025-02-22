#ifndef TEST_COMMON_INCL
#define TEST_COMMON_INCL

#include <stdio.h>

#define RED(s) "\x1b[41m" s "\x1b[0m"
#define GREEN(s) "\x1b[42m" s "\x1b[0m"

#define START_SUITE(suite_name)                                                \
  int tests_passed = 0, tests_failed = 0, tests_total = 0;                     \
  printf("Test Suite ---- %s\n", (suite_name));

#define ASSERT_INT_EQUAL(actual, expected, name)                               \
  {                                                                            \
    printf("  %s -- ", (name));                                                \
    if ((actual) != (expected)) {                                              \
      printf(RED("Failed") "\n");                                              \
      printf("\t" RED("Got %d") ", " GREEN("Expected %d") "\n\n", (actual),    \
             (expected));                                                      \
      tests_failed++;                                                          \
    } else {                                                                   \
      printf(GREEN("Passed\n\n"));                                             \
      tests_passed++;                                                          \
    }                                                                          \
    tests_total++;                                                             \
  }

#define ASSERT_INT_BETWEEN(actual, expected, error, name)                      \
  {                                                                            \
    printf("  %s -- ", (name));                                                \
    if ((actual) > (expected + error) || (actual) < (expected - error)) {      \
      printf(RED("Failed") "\n");                                              \
      printf("\t" GREEN("Got %d") ", " RED("Expected %d +/- %d\n\n"),          \
             (actual), (expected), (error));                                   \
      tests_failed--;                                                          \
    } else {                                                                   \
      printf(GREEN("Passed\n\n"));                                             \
      tests_passed++;                                                          \
    }                                                                          \
    tests_total++;                                                             \
  }

#define ASSERT_DOUBLE_BETWEEN(actual, expected, error, name)                   \
  {                                                                            \
    printf("  %s -- ", (name));                                                \
    if ((actual) > (expected + error) || (actual) < (expected - error)) {      \
      printf(RED("Failed\n"));                                                 \
      printf("\t" GREEN("Got %f")", " RED("Expected %f +/- %f\n\n"),           \
             (actual), (expected), (error));                                   \
    } else {                                                                   \
      printf(GREEN("Passed\n\n"));                                             \
      tests_passed++;                                                          \
    }                                                                          \
    tests_total++;                                                             \
  }

#define END_SUITE()                                                            \
  {                                                                            \
    printf("Tests Passed:\t%d\nTests Failed:\t%d\nTotal:\t%d\n\n",             \
           tests_passed, tests_failed, tests_total);                           \
                                                                               \
    if (tests_failed)                                                          \
      return 1;                                                                \
    return 0;                                                                  \
  }

#endif
