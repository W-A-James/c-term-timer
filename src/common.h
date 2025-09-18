#include <pthread.h>
#include <time.h>

typedef struct {
  int done;
  pthread_mutex_t lock;
} Done_t;

/**
 * Singleton struct used for synchronization of input processing thread and
 * clock thread
 */
extern Done_t done;

/**
 * initialize done struct
 */
void init_done(void);

/**
 * frees resources captured by initialized done struct
 */
void free_done(void);

/**
 * blocks trying to acquire lock on done struct and returns whether or not the
 * program is ending
 * */
int is_done(void);

/**
 * Blocks trying to acquire lock on done struct and marks the program as ending
 */
void set_done();

/**
 * Blocks trying to acquire lock on done struct and marks the program as not ending
 */
void clear_done();

/**
 * calls perror with provided argument and exits process with exit code 1
 * */
void die(const char *s);

/**
 * sleep for d milliseconds
 */
#define sleepms(d) (usleep((d)*1000))
