#include "./clock.h"
#include "./common.h"
#include "./duration-parser.h"
#include "./raw_term.h"

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

char read_key() {
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

void *process_input(void *_) {
  while (!is_done()) {
    // VTIME should be at least 1 so we block here to wait for some input and
    // ensure this isn't a busy loop
    char c = read_key();

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
  int duration_s = parse_duration(argc - 1, argv + 1);
  if (duration_s < 0)
    handle_error(duration_s);

  enable_raw_mode();
  init_done(done);
  // Start clock thread and input processing thread
  pthread_t clock_thread, input_processing_thread;

  pthread_create(&clock_thread, NULL, run, (void *)&duration_s);
  pthread_create(&input_processing_thread, NULL, process_input, NULL);

  pthread_join(clock_thread, NULL);
  pthread_join(input_processing_thread, NULL);

  free_done(done);
  return 0;
}
