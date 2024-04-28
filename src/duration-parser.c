#ifndef INCL_DURATION_PARSER
#define INCL_DURATION_PARSER
#include "./duration-parser.h"

#include "string.h"
#include "strings.h"
#include <ctype.h>
#include <stdlib.h>

int is_numeric(char *str) {
  int i = 0;
  while (str[i] != '\0') {
    if (!isdigit(str[i++]))
      return 0;
  }

  return 1;
}

int matches_time_w_suffix(int len, char *part, char suffix) {
  int i;
  for (i = 0; i < len - 1; i++) {
    if (!isdigit(part[i]))
      return 0;
  }
  return part[i] == suffix;
}

int parse_duration(int len, char **args) {
  int durationS = 0;
  int found_h = 0, found_m = 0, found_s = 0;

  // Check for seconds without suffix
  if (len == 1 && is_numeric(args[0])) {
    return atoi(args[0]);
  }

  for (int i = 0; i < len; i++) {
    if (matches_time_w_suffix(strlen(args[i]), args[i], 'h')) {
      if (found_h)
        return DUPLICATE_HOURS_SPEC;

      found_h = 1;
      // TODO: Fix this to get rid of suffix
      durationS += atoi(args[i]) * 3600;
      continue;
    }

    if (matches_time_w_suffix(strlen(args[i]), args[i], 'm')) {
      if (found_m)
        return DUPLICATE_MINUTES_SPEC;

      found_m = 1;
      // TODO: Fix this to get rid of suffix
      durationS += atoi(args[i]) * 60;
      continue;
    }

    if (matches_time_w_suffix(strlen(args[i]), args[i], 's')) {
      if (found_s)
        return DUPLICATE_SECONDS_SPEC;

      found_s = 1;
      // TODO: Fix this to get rid of suffix
      durationS += atoi(args[i]);
      continue;
    }

    return -1;
  }

  return durationS;
}
#endif
