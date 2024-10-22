//
// Created by ownen on 9/16/24.
//

#ifndef TERMINAL_H
#define TERMINAL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

/*struct TerminalStuff {*/
/*  int width;*/
/*  int height;*/
/*  int xPixel;*/
/*  int yPixel;*/
/*};*/

/* TODO: Replace This With TerminalStuff. */
typedef struct TerminalStuff {
  int width;
  int height;
  int xPixel;
  int yPixel;

} TerminalStuff;

void get_terminal_stuff(TerminalStuff *stuff);

void set_raw_mode(int fd, struct termios *original_termios);

void reset_mode(int fd, const struct termios *original_termios);

void print_centered_title(const int width, const int height, const char *text);

void print_centered_menu(const int width, const int height, char **lines,
                         int num_lines, int current_item);

void menu_page(int current_item, char **lines, int num_lines, int width,
               int height);

void clear_console();

char **split_text(const char *text, int *num_lines);

void draw_window(int width, int height);

void main_page();

#endif // TERMINAL_H
