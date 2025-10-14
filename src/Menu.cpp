#include <Menu.hpp>
#include <Utils.hpp>
#include <Constants.hpp>

Menu::Menu(int yMax, int xMax) : yMax(yMax), xMax(xMax) {

    std::string img = Utils::readFileToString(START_BUTTON);
    options.push_back(img);

    img = Utils::readFileToString(EXIT_BUTTON);
    options.push_back(img);

    img = Utils::readFileToString(LEFT_UP_CORNER);
    elements.push_back(img);

    img = Utils::readFileToString(RIGHT_UP_CORNER);
    elements.push_back(img);

    img = Utils::readFileToString(LEFT_DOWN_CORNER);
    elements.push_back(img);

    img = Utils::readFileToString(RIGHT_DOWN_CORNER);
    elements.push_back(img);
}

void Menu::draw() {
    clear();

    Utils::printMultiline(0, 0, elements[0]);
    Utils::printMultiline(0, xMax - 40, elements[1]);
    Utils::printMultiline(yMax - 18, xMax - 40, elements[2]);
    Utils::printMultiline(yMax - 18, 0, elements[3]);

    Utils::printMultiline(yMax/2 - 12, xMax/6, Utils::readFileToString(KNIGHT_ICON));
    int step = 8;

    for (size_t i = 0; i < options.size(); ++i) {
        if (static_cast<int>(i) == selected) {
            Utils::printMultiline(yMax/3 + step * i, xMax/2 - 12, options[i]);
        } else {
            Utils::printMultiline(yMax/3 + step * i, xMax/2 - 24, options[i]);
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
    Utils::printMultiline(yMax/2 - 3, xMax/2 - 35, Utils::readFileToString(GAMEOVER));
    Utils::printMultiline(yMax/2 - 12, 0, Utils::readFileToString(DEFEATED_KNIGHT));
    mvprintw(yMax/2 + 4, xMax/2 - 6, "press any key");
    getch();
}
