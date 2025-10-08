#pragma once
#include <string>
#include <ncurses.h>


void print_multiline(WINDOW *win, int start_y, int start_x, const std::string& text);

void print_multiline(int start_y, int start_x, const std::string& text);

std::string readFileToString(const std::string& filename);