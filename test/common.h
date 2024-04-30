#ifndef TEST_COMMON_INCL
#define TEST_COMMON_INCL

#define START_SUITE(suite_name)                                                \
  int tests_passed = 0, tests_failed = 0, tests_total = 0;                     \
  printf("Test Suite ---- %s\n", (suite_name));

#define ASSERT_INT_EQUAL(actual, expected, name)                               \
  {                                                                            \
    printf("  %s -- ", (name));                                                \
    if ((actual) != (expected)) {                                              \
      printf("\x1b[41mFailed\x1b[0m\n");                                       \
      printf("\t\x1b[41mGot %d\x1b[0m, \x1b[42mExpected %d\x1b[0m\n\n",        \
             (actual), (expected));                                            \
      tests_failed++;                                                          \
    } else {                                                                   \
      printf("\x1b[42mPassed\x1b[0m\n\n");                                     \
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
