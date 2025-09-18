#ifndef INCL_COMMON
#define INCL_COMMON
#include "./common.h"
#include <stdlib.h>
#include <stdio.h>

Done_t done;

void die(const char *s) {
  perror(s);
  exit(1);
}

void init_done(void) {
  done.done = 0;

  pthread_mutex_init(&done.lock, NULL);
  done.done = 0;
}

void free_done(void) {
  pthread_mutex_lock(&done.lock);
  pthread_mutex_unlock(&done.lock);

  pthread_mutex_destroy(&done.lock);
}

int is_done() {
  int is_done;
  pthread_mutex_lock(&done.lock);
  is_done = done.done;
  pthread_mutex_unlock(&done.lock);

  return is_done;
}

void set_done() {
  pthread_mutex_lock(&done.lock);
  done.done = 1;
  pthread_mutex_unlock(&done.lock);
}

void clear_done() {
  pthread_mutex_lock(&done.lock);
  done.done = 0;
  pthread_mutex_unlock(&done.lock);
}

#endif
