#include "database.h"

#include <sqlite3.h>
#include <stdio.h>

int open_connetion(char *db_name, sqlite3 **db) {
  int rc = sqlite3_open(db_name, db);

  if (rc) {
    fprintf(stderr, "Can`t open database: %s\n", sqlite3_errmsg(*db));
    return rc;
  }

  fprintf(stdout, "Opened database successfuly\n");
  return SQLITE_OK;
}

int create_init_tables(sqlite3 *db) {
  char *errMsg = 0;
  const char *book_sql = "CREATE TABLE IF NOT EXISTS books ("
                         "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                         "name TEXT NOT NULL,"
                         "description NOT NULL,"
                         "is_e_book INTEGER NOT NULL DEFAULT 1,"
                         "file_type TEXT NOT NULL,"
                         "file_name TEXT NULL);";

  sqlite3_exec(db, book_sql, 0, 0, &errMsg);
  if (errMsg != 0) {
    printf("%s\n", errMsg);
    return 1;
  }
  return 0;
}
