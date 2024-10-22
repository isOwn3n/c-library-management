#include "database.h"
#include "terminal.h"
#include "utils.h"

#include <signal.h>
#include <sqlite3.h>
#include <stdio.h>

// TODO: Move it to
int get_array_length(char **array) {
  int length = 0;
  while (array[length] != NULL) length++;
  return length;
}

int main() {
  sqlite3 *db;

  int c;
  // TODO: Uncomment ignoring signal function.
  /*signal(SIGINT, ignore_signal);*/

  struct TerminalStuff term_stuff;
  struct termios original_termios;

  // Hide Cursor Using ANSI
  printf("\033[?25l");

  char *print_text = "Main\nCreate\nUpdate\nExit\0";

  int num_lines;
  char **lines = split_text(print_text, &num_lines);

  run_once(original_termios, db, term_stuff);

  int current_item = 0;
  while (1) {
    terminal_action(current_item, lines, num_lines, term_stuff);
  }
  onexit(original_termios, num_lines, lines, db);
  return 0;
}
