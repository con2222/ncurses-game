#pragma once
#include <string>
#include <ncurses.h>


void printMultiline(WINDOW *win, int start_y, int start_x, const std::string& text);

void printMultiline(int start_y, int start_x, const std::string& text);

std::string readFileToString(const std::string& filename);

void printNumbers(int y, int x, int number);