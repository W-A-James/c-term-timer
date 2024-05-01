#include "../src/clock.h"
#include "../src/common.h"

#include "./common.h"
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

double diff(struct timeval start, struct timeval end) {
  long long start_sec, start_usec, end_sec, end_usec, diff_sec, diff_usec;
  start_sec = (long long)start.tv_sec;
  start_usec = (long long)start.tv_usec;
  end_sec = (long long)end.tv_sec;
  end_usec = (long long)end.tv_usec;

  diff_sec = end_sec - start_sec;
  diff_usec = end_usec - start_usec;

  if (diff_usec < 0 && diff_sec > 0) {
    diff_sec--;
    diff_usec += 1000000;
  }

  return (double)diff_sec + ((double)diff_usec) / 1000000.0;
}

int main(int argc, char **argv) {
  struct timeval start, end;
  double difference;
  int duration = 1;

  char name[20];

  START_SUITE("clock")

  for (int i = 1; i <= 10; i++) {
    // when run with 1s, has 0.05s accuracy
    gettimeofday(&start, NULL);
    clock_run((void *)&duration);
    gettimeofday(&end, NULL);

    printf("\n\n\n\n");
    clear_done();

    difference = diff(start, end);

    memset(&name, 0, 20);
    sprintf(name, "Clock accuracy %d", i);
    ASSERT_DOUBLE_BETWEEN(difference, 1.0, 0.05, name)
  }

  END_SUITE()
}
