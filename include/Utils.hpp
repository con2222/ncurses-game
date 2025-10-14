#pragma once
#include <string>
#include <ncurses.h>

class Utils {
public:
    static void printMultiline(WINDOW *win, int start_y, int start_x, const std::string& text);
    static void printMultiline(int start_y, int start_x, const std::string& text);
    static std::string readFileToString(const std::string& filename);
    static void printNumbers(int y, int x, int number);
};