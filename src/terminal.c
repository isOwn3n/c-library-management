/*
 Created by Ownen on 9/16/24.
*/

#include "terminal.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

/*
 * It is i function to get terminal size and pixels.
 * It modify the struct that passed as parameter.
 */
void get_terminal_stuff(struct TerminalStuff *stuff) {
  struct winsize w;

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
    // default size (80x24)
    stuff->width = 80;
    stuff->height = 24;
    stuff->xPixel = 80;
    stuff->yPixel = 24;
  } else {
    stuff->width = w.ws_col;
    stuff->height = w.ws_row;
    stuff->xPixel = w.ws_xpixel;
    stuff->yPixel = w.ws_ypixel;
  }
}

/*
 * This function set raw mode in terminal because characters are directly
 * read from and written to the device without any translation or
 * interpretation by the operating system.
 */
void set_raw_mode(const int fd, struct termios *original_termios) {
  struct termios raw;
  tcgetattr(fd, original_termios);
  raw = *original_termios;

  raw.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(fd, TCSANOW, &raw);
}

void reset_mode(const int fd, const struct termios *original_termios) {
  tcsetattr(fd, TCSANOW, original_termios);
}

char **split_text(const char *text, int *num_lines) {
  int count = 1;
  for (const char *p = text; *p; p++) {
    if (*p == '\n') {
      count++;
    }
  }

  char **lines = malloc(count * sizeof(char *));
  if (lines == NULL) {
    perror("Failed to allocate memory");
    return NULL;
  }

  const char *start = text;
  int line_index = 0;
  while (*start) {
    const char *end = strchr(start, '\n');
    if (end == NULL) {
      end = start + strlen(start);
    }

    size_t length = end - start;
    lines[line_index] = malloc(length + 1);
    if (lines[line_index] == NULL) {
      perror("Failed to allocate memory");
      for (int i = 0; i < line_index; i++) {
        free(lines[i]);
      }
      free(lines);
      return NULL;
    }

    // Copy the line and add a null terminator
    strncpy(lines[line_index], start, length);
    lines[line_index][length] = '\0';

    line_index++;
    start = end + 1;
  }

  *num_lines = count;
  return lines;
}

void print_centered_title(const int width, const int height, const char *text) {
  int num_lines;
  char **lines = split_text(text, &num_lines);

  if (lines != NULL) {
    const int start_y = (height - num_lines) / 2;

    for (int i = 0; i < num_lines; i++) {
      char *single_text = lines[i];
      const int text_length = strlen(single_text);
      const int padding = (width - text_length) / 2;

      printf("\033[%d;%dH", start_y + i + 1, 1);
      for (int j = 0; j < padding; j++) {
        printf(" ");
      }
      printf("%s", single_text);
    }
    printf("\n");

    for (int i = 0; i < num_lines; i++) {
      free(lines[i]);
    }
    free(lines);
  }
  exit(1);
}

void print_centered_menu(const int width, const int height, char **lines,
                         int num_lines, int current_item) {
  if (lines != NULL) {
    const int start_y = ((height - num_lines) / 2) + 2;

    for (int i = 0; i < num_lines; i++) {
      char *single_text = lines[i];
      const int text_length = strlen(single_text);
      int padding = (width - text_length) / 2;

      if (i == current_item)
        padding -= 2;

      printf("\033[%d;%dH%*s", start_y + i + 1, 1, padding, "");

      if (i == current_item) {
        printf("> %s <", single_text);
      } else {
        printf("%s", single_text);
      }
    }

    printf("\n");
  }
  exit(1);
}

void clear_console() { printf("\033[H\033[J"); }

void menu_page(int current_item, char **lines, int num_lines, int width,
               int height) {
  clear_console();
  print_centered_menu(width, height, lines, num_lines, current_item);
}

void main_page() {}

void move_cursor(int x, int y) { printf("\033[%d;%dH", y, x); }

void print_char(char *c) { putchar(*c); }

void print_utf8(const char *utf8) {
  while (*utf8) {
    putchar(*utf8++);
  }
}

/*
 * TODO: Modify This Function
 */
void draw_window(int width, int height) {
  char *top_left_corner = "╔";
  char *top_right_corner = "╗";
  char *bottom_left_corner = "╚";
  char *bottom_right_corner = "╝";
  char *horizontal_border = "═";
  char *vertical_border = "║";

  // Draw horizontal borders
  for (int x = 1; x < width - 1; x++) {
    move_cursor(x, 0);
    print_utf8(horizontal_border);
    move_cursor(x, height - 1);
    print_utf8(horizontal_border);
  }

  // Draw vertical borders
  for (int y = 1; y < height - 1; y++) {
    move_cursor(0, y);
    print_utf8(vertical_border);
    move_cursor(width - 1, y);
    print_utf8(vertical_border);
  }
  move_cursor(0, 0);
  print_utf8(top_left_corner);

  fflush(stdout);
}
