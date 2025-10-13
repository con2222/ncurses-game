#include <Menu.hpp>
#include <Utils.hpp>
#include <Constants.hpp>

Menu::Menu(int yMax, int xMax) : yMax(yMax), xMax(xMax) {

    std::string img = readFileToString(START_BUTTON);
    options.push_back(img);

    img = readFileToString(EXIT_BUTTON);
    options.push_back(img);

    img = readFileToString(LEFT_UP_CORNER);
    elements.push_back(img);

    img = readFileToString(RIGHT_UP_CORNER);
    elements.push_back(img);

    img = readFileToString(LEFT_DOWN_CORNER);
    elements.push_back(img);

    img = readFileToString(RIGHT_DOWN_CORNER);
    elements.push_back(img);
}

void Menu::draw() {
    clear();

    printMultiline(0, 0, elements[0]);
    printMultiline(0, xMax - 40, elements[1]);
    printMultiline(yMax - 18, xMax - 40, elements[2]);
    printMultiline(yMax - 18, 0, elements[3]);

    printMultiline(yMax/2 - 12, xMax/6, readFileToString(KNIGHT_ICON));
    int step = 8;

    for (size_t i = 0; i < options.size(); ++i) {
        if (static_cast<int>(i) == selected) {
            printMultiline(yMax/3 + step * i, xMax/2 - 12, options[i]);
        } else {
            printMultiline(yMax/3 + step * i, xMax/2 - 24, options[i]);
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
    }
}

void Menu::gameOver() {
    flushinp();
    printMultiline(yMax/2 - 3, xMax/2 - 35, readFileToString(GAMEOVER));
    printMultiline(yMax/2 - 12, 0, readFileToString(DEFEATED_KNIGHT));
    mvprintw(yMax/2 + 4, xMax/2 - 6, "press any key");
    getch();
}
