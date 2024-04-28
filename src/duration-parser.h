enum PARSE_ERROR {
  DUPLICATE_HOURS_SPEC_ERR = -1,
  DUPLICATE_MINUTES_SPEC_ERR = -2,
  DUPLICATE_SECONDS_SPEC_ERR = -3,
  NON_NUMERIC_INPUT_ERR = -4,
  UNKNOWN_TIME_SPECIFIER_ERR = -5
};

/**
 * parse a duration in seconds from command line args provided as follows
 *
 * <x>h <y>m <z>s where at least one of x, y or z must be provided
 *
 * returns positive integer representing total time in seconds on success,
 * returns negative integer on failure
 */
int parse_duration(int len, char **args);

/**
 * Prints message corresponding to values in PARSE_ERROR enum and exits program
 */
void handle_error(enum PARSE_ERROR errcode);
