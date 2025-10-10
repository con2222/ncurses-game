#pragma once

enum class ColorPair : int {
    PLAYER = 1,
    ENEMY = 2,
    WALL = 3,
    BG = 4,
    BATTLE_BUTTON = 5,
};

void initGameColors();