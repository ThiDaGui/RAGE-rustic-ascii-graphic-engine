#include <ncurses.h>

WINDOW      *window_create(int width, int height, int startx, int starty) {
    WINDOW  *win = newwin(height, width, starty, startx);
    if (win == NULL)
        return NULL;

    wrefresh(win);

    return win;
}

void        window_delete(WINDOW *win) {
    wrefresh(win);
    delwin(win);
}