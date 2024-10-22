//
// Created by ownen on 9/16/24.
//

#ifndef UTILS_H
#define UTILS_H
#include "terminal.h" // For TerminalStuff
#include <sqlite3.h>  // For sqlite3
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h> // For termios

void ignore_signal(int sig);

int get_number_of_lines(char *text);
int terminal_action(int current_item, char **lines, int num_lines,
                    TerminalStuff term_stuff);

void onexit(struct termios original_termios, int num_lines, char **lines,
            sqlite3 *db);

void run_once(struct termios original_termios, sqlite3 *db,
              TerminalStuff term_stuff);

#endif // UTILS_H
