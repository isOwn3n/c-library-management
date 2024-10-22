#ifndef ENV_FILE_H

#define ENV_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char *trim_whitespace(char* str);

void parse_env_file(const char *filename);

#endif // ENV_FILE_H
