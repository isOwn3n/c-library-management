cmake_minimum_required(VERSION 3.29)
project(tui-library C)

set(CMAKE_C_STANDARD 11)
find_package(SQLite3 REQUIRED)

include_directories(includes)

set(SOURCES
        src/main.c
        src/terminal.c
        src/utils.c
        src/env_file.c
        src/database.c
)

add_executable(tui-library ${SOURCES})

target_link_libraries(tui-library SQLite::SQLite3)
