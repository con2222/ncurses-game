#pragma once
#include <ncurses.h>
#include <vector>
#include <string>

class Menu {
public:
    Menu(int height, int width);
    ~Menu();

    bool init();

    void deinit();
private:
    void draw();
    int height;
    int width;
    WINDOW* menu;

    std::vector<std::string> options = {"Start Game", "Exit"};
    int selected = 0;
};

