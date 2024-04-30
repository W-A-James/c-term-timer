#ifndef INCL_CLOCK
#define INCL_CLOCK
#include "./clock.h"
#include "./common.h"
#include "./raw_term.h"

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

char *CLOCK_FMT_STRING = "╭──────────╮\r\n"
                         "│ %02d:%02d:%02d │\r\n"
                         "╰──────────╯\r\n";

void *run(void *durationP) {
  int durationS = *((int *)durationP);
  int hours, minutes, seconds;

  while (durationS > 0 && !is_done()) {

    hours = durationS / 3600;
    minutes = (durationS % 3600) / 60;
    seconds = (durationS % 60);
    durationS--;
    printf(CLOCK_FMT_STRING, hours, minutes, seconds);
    move_cursor(0, -3);

    // Wait for 1000ms in increments of 50ms
    for (int i = 0; i < 10; i++) {
      if (is_done()) {
        return NULL;
      }
      sleepms(100);
    }
  }

  if (durationS == 0) { // Timer expired
    printf("\x07");
    set_done();
  }
  return NULL;
}
#endif
