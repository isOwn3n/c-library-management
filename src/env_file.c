#include "env_file.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Remove leading and trailing whitespace. */
char *trim_whitespace(char *str) {
  while (isspace((unsigned char)*str))
    str++;

  if (*str == 0)
    return str;

  char *end = str + strlen(str) - 1;

  while (end > str && isspace((unsigned char)*end))
    end--;

  end[1] = '\0';
  return str;
}

void parse_env_file(const char *filename) {
  FILE *file = fopen(filename, "r");

  if (file == NULL) {
    fprintf(stderr, "Could not open .env file\n");
    return;
  }

  char line[256];
  while (fgets(line, sizeof(line), file)) {
    if (line[0] == '#' || line[0] == '\n')
      continue;
    char *key = strtok(line, "=");
    char *value = strtok(NULL, "=");

    if (key && value) {
      key = trim_whitespace(key);
      value = trim_whitespace(value);

      setenv(key, value, 1);
    }
  }

  fclose(file);
}
