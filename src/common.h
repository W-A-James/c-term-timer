#include <pthread.h>
#include <time.h>

typedef struct {
  int done;
  pthread_mutex_t lock;
} Done_t;

extern Done_t done;

void init_done();

void free_done();

int is_done();

void set_done();

void die(const char *s);

#define sleepms(d) (usleep((d)*1000))
