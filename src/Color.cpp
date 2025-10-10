#include <Color.hpp>
#include <ncurses.h>

void initGameColors() {
    if (has_colors()) {
        start_color();
        init_pair(static_cast<int>(ColorPair::PLAYER), COLOR_GREEN, COLOR_BLACK);
        init_pair(static_cast<int>(ColorPair::ENEMY),  COLOR_RED,   COLOR_BLACK);
        init_pair(static_cast<int>(ColorPair::WALL),   COLOR_WHITE, COLOR_BLACK);
        init_pair(static_cast<int>(ColorPair::BG),     COLOR_BLACK, COLOR_BLACK);
        init_pair(static_cast<int>(ColorPair::BATTLE_BUTTON), COLOR_BLACK, COLOR_WHITE);
    }
}