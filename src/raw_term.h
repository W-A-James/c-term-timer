/**
 * Restore terminal to configuriong at start of program
 */
void disable_raw_mode(void);

/**
 * Put terminal in raw mode and resgister disable_raw_mode to be called on exit
 * */
void enable_raw_mode(void);

/**
 * Move terminal cursor relative to current position
 */
void move_cursor(int dx, int dy);

/**
 * clear line from current cursor position to end of line
 * */
void clear_line(void);
