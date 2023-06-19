/**
 * @file win.c
 * @brief win.h implementation
 * @version 0.1
 * @date 2023-06-19
 */
#include <ncurses.h>

WINDOW *window_create(size_t width, size_t height, size_t startx, size_t starty)
{
    WINDOW *win = newwin(height, width, starty, startx);
    if (win == NULL)
        return NULL;

    wrefresh(win);

    return win;
}

void window_delete(WINDOW *win)
{
    wrefresh(win);
    delwin(win);
}
