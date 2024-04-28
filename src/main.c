#include "./clock.h"
#include "./common.h"
#include "./raw_term.h"
#include "./duration-parser.h"

#include <ctype.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*** defines ***/

/*
 * Convert character to code when ctrl is pressed
 */
#define CTRL_KEY(k) ((k)&0x1f)

char readKey() {
  int nread;
  char c;

  while (1) {
    nread = read(STDIN_FILENO, &c, 1);
    if (nread == -1 && errno != EAGAIN)
      die("read");
    else
      break;
  }

  return c;
}

void *processInput(void *_) {
  while (!is_done()) {
    char c = readKey();

    switch (c) {
    case CTRL_KEY('q'):
    case CTRL_KEY('c'):
      set_done();
      break;
    }
  }

  return NULL;
}

int main(int argc, char **argv) {
  int durationS = parse_duration(argc - 1, argv + 1);

  enableRawMode();
  init_done(done);
  // Start clock thread and input processing thread
  pthread_t clock_thread, input_processing_thread;
  void *rv;

  pthread_create(&clock_thread, NULL, run, (void *)&durationS);
  pthread_create(&input_processing_thread, NULL, processInput, NULL);

  pthread_join(clock_thread, &rv);
  pthread_join(input_processing_thread, &rv);

  free_done(done);
  return 0;
}
