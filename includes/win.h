/**
 * @file win.h
 * @brief window header file
 * @details this file contains the window functions. The window is created with
 * ncurses library
 * @version 0.1
 * @date 2023-06-19
 */
#ifndef WIN_H
#define WIN_H

#include <ncurses.h>
/**
 * @brief create a window with ncurses library of size width x height and start
 * at startx, starty
 * @param width width of the window
 * @param height height of the window
 * @param startx
 * @param starty
 * @return the newly created window or NULL if error
 */
WINDOW *window_create(size_t width, size_t height, size_t startx,
                      size_t starty);
/**
 * @brief delete the window
 * @param win the window to delete
 */
void window_delete(WINDOW *win);

#endif
