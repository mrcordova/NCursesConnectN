cmake_minimum_required(VERSION 3.13)
project(NCursesConnectN LANGUAGES C)

set(CMAKE_C_STANDARD 11)

add_executable(NCursesConnectN main.c board.h board.c player.c player.h checkWin.c checkWin.h)

set(CURSES_USE_NCURSES TRUE)
find_package(Curses REQUIRED)

target_compile_options(NCursesConnectN PRIVATE -Wall -Werror)
target_link_libraries(NCursesConnectN PRIVATE ${CURSES_LIBRARIES})
target_include_directories(NCursesConnectN PRIVATE ${CURSES_INCLUDE_DIRS})