#ifndef WIN_H
#define WIN_H

#include <ncurses.h>

WINDOW *window_create(size_t width, size_t height, size_t startx,
                      size_t starty);

void window_delete(WINDOW *win);

#endif
