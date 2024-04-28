#ifndef INCL_DURATION_PARSER
#define INCL_DURATION_PARSER
#include "./duration-parser.h"

#include "string.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int is_numeric(char *str) {
  int i = 0;
  while (str[i] != '\0') {
    if (!isdigit(str[i++]))
      return 0;
  }

  return 1;
}

int is_numeric_n(int len, char *str) {
  for (int i = 0; i < len; i++) {
    if (!isdigit(str[i]))
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
    int len = strlen(args[i]);

    if (!is_numeric_n(len - 1, args[i])) {
      return NON_NUMERIC_INPUT_ERR;
    }

    switch (args[i][len - 1]) {
    case 'h':
    case 'H':
      if (found_h)
        return DUPLICATE_HOURS_SPEC_ERR;
      found_h = 1;
      durationS += atoi(args[i]) * 3600;
      continue;
    case 'm':
    case 'M':
      if (found_m)
        return DUPLICATE_MINUTES_SPEC_ERR;
      found_m = 1;
      durationS += atoi(args[i]) * 60;
      continue;
    case 's':
    case 'S':
      if (found_s)
        return DUPLICATE_SECONDS_SPEC_ERR;
      found_s = 1;
      durationS += atoi(args[i]);
      continue;
    default:
      return UNKNOWN_TIME_SPECIFIER_ERR;
    }
  }

  return durationS;
}

void handle_error(enum PARSE_ERROR errcode) {
  switch (errcode) {
  case DUPLICATE_HOURS_SPEC_ERR:
    fprintf(stderr, "Found duplicate hour specifier\n");
    break;
  case DUPLICATE_MINUTES_SPEC_ERR:
    fprintf(stderr, "Found duplicate minute specifier\n");
    break;
  case DUPLICATE_SECONDS_SPEC_ERR:
    fprintf(stderr, "Found duplicate second specifier\n");
    break;
  case NON_NUMERIC_INPUT_ERR:
    fprintf(stderr, "Found non-numeric time specifier\n");
    break;
  case UNKNOWN_TIME_SPECIFIER_ERR:
    fprintf(stderr, "Found unknown specifier\n");
    break;
  }

  exit(1);
}
#endif
