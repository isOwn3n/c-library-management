#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <stdio.h>

int open_connetion(char *db_name, sqlite3 **db);

int create_init_tables(sqlite3 *db);

#endif // DATABASE_H
