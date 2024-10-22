//
// Created by ownen on 9/16/24.
//

#include "utils.h"
#include "database.h"
#include "env_file.h"
#include "terminal.h"

/*#include <sys/ioctl.h>*/
#include <termios.h>

void ignore_signal(int sig) {}

int get_number_of_lines(char *text) {
  int count = 1;

  for (int i = 0; text[i] != '\0'; i++)
    if (text[i] == '\n')
      count++;

  return count;
}

int terminal_action(int current_item, char **lines, int num_lines,
                    TerminalStuff term_stuff) {
  int c;
  menu_page(current_item, lines, num_lines, term_stuff.width,
            term_stuff.height);

  c = getchar();

  if (c == 'q')
    // 0 Is False
    return 0;

  else if (c == '\033') {
    getchar();
    switch (getchar()) {
    case 'A':
      if (current_item > 0)
        current_item--;
      break;
    case 'B':
      if (current_item < num_lines - 1)
        current_item++;

      break;
    // case 'C':
    // Right Arrow
    //    break;
    // case 'D':
    // Left Arrow
    //    break;
    default:
      break;
    }
  } else if (c == '\n') {
    if (current_item == num_lines - 1)
      return 0;
  }
  return 1;
}

void terminal_init(TerminalStuff term_stuff, struct termios original_termios) {

  get_terminal_stuff(&term_stuff);
  set_raw_mode(STDIN_FILENO, &original_termios);

  clear_console();
  draw_window(term_stuff.width, term_stuff.height);
}

void db_init(sqlite3 **db) {
  char *db_name = getenv("DB_NAME");
  if (db_name == NULL) {
    fprintf(stderr, "Could not find var in file.\n");
    exit(1);
  }
  int result = open_connetion(db_name, db);
  if (result != SQLITE_OK) {
    fprintf(stderr, "Could not open database: %s\n.", db_name);
    exit(1);
  }

  int created = create_init_tables(*db);
  if (created) {
    fprintf(stderr, "Could Not Create New Table In DB.");
    exit(1);
  }
}

void env_init() {
  char *env_location = "../.env";
  parse_env_file(env_location);
}

void run_once(struct termios original_termios, sqlite3 *db,
              TerminalStuff term_stuff) {
  env_init();
  db_init(&db);
  terminal_init(term_stuff, original_termios);
}

void onexit(struct termios original_termios, int num_lines, char **lines,
            sqlite3 *db) {
  clear_console();
  reset_mode(STDIN_FILENO, &original_termios);
  printf("\033[?25h");

  for (int i = 0; i < num_lines; i++)
    free(lines[i]);

  free(lines);
  sqlite3_close(db);
}
