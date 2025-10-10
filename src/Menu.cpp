#include "Menu.hpp"
#include <unistd.h> 

Menu::Menu(int height, int width)
    : height(height), width(width) {
    int win_h = 10;
    int win_w = 30;
    int start_y = height / 2 - win_h / 2;
    int start_x = width / 2 - win_w / 2;

    menu = newwin(win_h, win_w, start_y, start_x);
    keypad(menu, TRUE);
}

void Menu::draw() {
    werase(menu);
    box(menu, 0, 0);
    mvwprintw(menu, 1, 30/2 - 8, "=== MAIN MENU ===");

    for (size_t i = 0; i < options.size(); ++i) {
        if (static_cast<int>(i) == selected) {
            wattron(menu, A_REVERSE);
            mvwprintw(menu, 3 + static_cast<int>(i), 30/2 - options[i].size()/2, "%s", options[i].c_str());
            wattroff(menu, A_REVERSE);
        } else {
            mvwprintw(menu, 3 + static_cast<int>(i), 30/2 - options[i].size()/2, "%s", options[i].c_str());
        }
    }
    wrefresh(menu);
}

bool Menu::init() {
    int ch;
    bool running = true;

    while (true) {
        draw();
        ch = wgetch(menu);

        switch (ch) {
            case KEY_UP:
                if (selected > 0) selected--;
                break;
            case KEY_DOWN:
                if (selected < static_cast<int>(options.size()) - 1) selected++;
                break;
            case '\n': 
                if (options[selected] == "Exit") {
                    return 0;
                } else if (options[selected] == "Start Game") {
                    return 1;
                }

                break;
            case 'q':
            case 27: 
                running = false;
                break;
        }

        usleep(10000); 
    }
}

void Menu::deinit() {
    if (menu) {
        werase(menu);      
        wrefresh(menu);    
        delwin(menu);      
        menu = nullptr;
    }
}

Menu::~Menu() {
    deinit();
}