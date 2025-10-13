#pragma once
#include <ncurses.h>
#include <vector>
#include <string>

class Menu {
public:
    Menu(int yMax, int xMax);

    bool init();
    void gameOver();

private:
    void draw();
    int yMax;
    int xMax;

    std::vector<std::string> options;
    std::vector<std::string> elements;
    int selected = 0;
};