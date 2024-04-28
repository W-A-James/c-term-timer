#include "../src/duration-parser.h"

char *hours_mins_secs = "2h 5m 3s";
char *hours_mins = "2h 3s";
char *hours_secs = "5s";

char *mins_secs = "10m 6s";
char *mins = "10m";

char *secs = "10s";
char *secs_no_suffix = "10";

char *unrecognized_specifier = "100ta";

char *duplicate_hour = "1h 2h";
char *duplicate_minutes = "1m 2m";
char *duplicate_seconds = "1s 2s";

int main(int argc, char **argv) {
  // When passed a string of the format <x>h <y>m <z>s
  // When passed a string of the format <x>h <y>m
  // When passed a string of the format <x>h <y>s

  // When passed a string of the format <x>m <y>s
  // When passed a string of the format <x>m

  // When passed a string of the format <x>s
  // When passed a string of the format <x>

  // When passed a string with an unrecognized time specifier
  // When passed duplicate hour specifiers
  // When passed duplicate minute specifiers
  // When passed duplicate second specifiers
}
