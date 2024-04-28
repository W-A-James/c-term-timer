#ifndef INCL_RAW_TERM
#define INCL_RAW_TERM

/*** includes  ***/

#include "./common.h"

#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

/*** data ***/

struct termios orig_termios;

/*** terminal funcitons ***/

void disable_raw_mode(void) {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    die("tcsetattr");
}

void enable_raw_mode(void) {
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
    die("tcgetattr");

  atexit(disable_raw_mode);

  struct termios raw = orig_termios;

  raw.c_iflag &= ~(IXON     // Disable Ctrl-s and Ctrl-q
                   | ICRNL  // Disable ctrl-m as newline
                   | BRKINT // Disable break condition generating sigint
                   | INPCK  // Disable parity checking (legacy)
                   | ISTRIP // disable dropping of 8th bith of each input byte
  );
  raw.c_oflag &= ~(OPOST // turn off output post-processing
  );
  raw.c_cflag |= (CS8);     // set character size to 8bits per byte
  raw.c_lflag &= ~(ECHO     // Disable echo
                   | ICANON // Disbale canonical mode
                   | ISIG   // Disable signal inputs (ctrl-c, ctrl-z)
                   | IEXTEN // Disable  ctrl-v, ctrl-o
  );

  raw.c_cc[VMIN] =
      0; // set minimum number of bytes needed before read can return to 0
  raw.c_cc[VTIME] = 1; // set max time to wait for read to return to 0.1s

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
    die("tcsetattr");
}

void move_cursor(int dx, int dy) {
  int nwrite, xEscapeWidth, yEscapeWidth, absdx, absdy;
  char *xReposFmt, *yReposFmt, reposStr[10];

  memset(reposStr, 0, 10);

  absdx = abs(dx);
  absdy = abs(dy);

  xEscapeWidth = absdx >= 10 ? (int)ceilf(log10f(absdx)) + 3 : 4;
  yEscapeWidth = absdy >= 10 ? (int)ceilf(log10f(absdy)) + 3 : 4;

  // printf("xEscapeWidth: %d, yEscapeWidth: %d\r\n", xEscapeWidth,
  // yEscapeWidth);

  if (dx < 0)
    xReposFmt = "\x1b[%dD";
  else
    xReposFmt = "\x1b[%dC";

  if (dy < 0)
    yReposFmt = "\x1b[%dA";
  else
    yReposFmt = "\x1b[%dB";

  // Adjust y pos
  if (dy != 0) {
    // printf("Adjusting y pos by %d\r\n", dy);
    sprintf(reposStr, yReposFmt, absdy);
    nwrite = write(STDOUT_FILENO, reposStr, yEscapeWidth);
    if (nwrite == -1 && errno != EAGAIN) {
      die("write");
    }
  }

  // Adjust x pos
  if (dx != 0) {
    // printf("Adjusting x pos by %d\r\n", dx);
    sprintf(reposStr, xReposFmt, absdx);
    nwrite = write(STDOUT_FILENO, reposStr, xEscapeWidth);
    if (nwrite == -1 && errno != EAGAIN) {
      die("write");
    }
  }
}

void clear_line(void) {
  if (write(STDOUT_FILENO, "\x1b[K", 3) == -1 && errno != EAGAIN) {
    die("write");
  }
}

#endif
