#include "../src/duration-parser.h"

#include "./common.h"
#include <stdio.h>

char *hours_mins_secs[3] = {"2h", "5m", "3s"};
char *hours_mins[2] = {"2h", "3m"};
char *hours_secs[2] = {"2h", "5s"};

char *mins_secs[2] = {"10m", "6s"};
char *mins[1] = {"10m"};

char *secs[1] = {"10s"};
char *secs_no_suffix[1] = {"10"};

char *unrecognized_specifier[1] = {"100t"};
char *non_numeric[1] = {"abcdt"};

char *duplicate_hour[2] = {"1h", "2h"};
char *duplicate_minutes[2] = {"1m", "2m"};
char *duplicate_seconds[2] = {"1s", "2s"};

int main(int argc, char **argv) {
  START_SUITE("duration-parser")
  // When passed a string of the format <x>h <y>m <z>s
  ASSERT_INT_EQUAL(parse_duration(3, hours_mins_secs), 2 * 3600 + 5 * 60 + 3,
                   "Hours, minutes and seconds test")
  // When passed a string of the format <x>h <y>m
  ASSERT_INT_EQUAL(parse_duration(2, hours_mins), 2 * 3600 + 3 * 60,
                   "Hours and minutes test")
  // When passed a string of the format <x>h <y>s
  ASSERT_INT_EQUAL(parse_duration(2, hours_secs), 2 * 3600 + 5,
                   "Hours and seconds test")

  // When passed a string of the format <x>m <y>s
  ASSERT_INT_EQUAL(parse_duration(2, mins_secs), 10 * 60 + 6,
                   "Minutes and seconds test")

  // When passed a string of the format <x>m
  ASSERT_INT_EQUAL(parse_duration(1, mins), 10 * 60, "Minutes test")

  // When passed a string of the format <x>s
  ASSERT_INT_EQUAL(parse_duration(1, secs), 10, "Seconds test")
  // When passed a string of the format <x>
  ASSERT_INT_EQUAL(parse_duration(1, secs_no_suffix), 10,
                   "Seconds w/o suffix test")

  // When passed a string with an unrecognized time specifier
  ASSERT_INT_EQUAL(parse_duration(1, unrecognized_specifier),
                   UNKNOWN_TIME_SPECIFIER_ERR, "Unrecognized specifier test")
  // When passed a non-numeric string
  ASSERT_INT_EQUAL(parse_duration(1, non_numeric),

                   NON_NUMERIC_INPUT_ERR, "Non numeric input test")
  // When passed duplicate hour specifiers
  ASSERT_INT_EQUAL(parse_duration(2, duplicate_hour), DUPLICATE_HOURS_SPEC_ERR,
                   "Duplicate hours test")
  // When passed duplicate minute specifiers
  ASSERT_INT_EQUAL(parse_duration(2, duplicate_minutes),
                   DUPLICATE_MINUTES_SPEC_ERR, "Duplicate minutes test")
  // When passed duplicate second specifiers
  ASSERT_INT_EQUAL(parse_duration(2, duplicate_seconds),
                   DUPLICATE_SECONDS_SPEC_ERR, "Duplicate seconds test")

  END_SUITE()
}
