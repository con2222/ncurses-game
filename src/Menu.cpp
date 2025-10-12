#include "Menu.hpp"
#include <unistd.h>
#include <Utils.hpp>

Menu::Menu(int yMax, int xMax) : yMax(yMax), xMax(xMax) {

    std::string img = readFileToString("../assets/menu/start.txt");
    options.push_back(img);

    img = readFileToString("../assets/menu/exit.txt");
    options.push_back(img);

    img = readFileToString("../assets/menu/2.txt");
    elements.push_back(img);

    img = readFileToString("../assets/menu/1.txt");
    elements.push_back(img);

    img = readFileToString("../assets/menu/3.txt");
    elements.push_back(img);

    img = readFileToString("../assets/menu/4.txt");
    elements.push_back(img);
}

void Menu::draw() {
    clear();
    
    print_multiline(0, 0, elements[0]);
    print_multiline(0, xMax - 40, elements[1]);
    print_multiline(yMax - 18, xMax - 40, elements[2]);
    print_multiline(yMax - 18, 0, elements[3]);
    int step = 8;

    for (size_t i = 0; i < options.size(); ++i) {
        if (static_cast<int>(i) == selected) {
            attron(A_REVERSE);
            print_multiline(yMax/4 + step * i, xMax/2 - 12, options[i]);
            attroff(A_REVERSE);
        } else {
            print_multiline(yMax/4 + step * i, xMax/2 - 9, options[i]);
        }
    }
    refresh();
}

bool Menu::init() {
    int ch;
    bool running = true;

    while (true) {
        draw();
        ch = getch();

        switch (ch) {
            case KEY_UP:
                if (selected > 0) selected--;
                break;
            case KEY_DOWN:
                if (selected < static_cast<int>(options.size()) - 1) selected++;
                break;
            case '\n': 
                if (selected == 1) {
                    return 0;
                } else if (selected == 0) {
                    clear();
                    refresh();
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