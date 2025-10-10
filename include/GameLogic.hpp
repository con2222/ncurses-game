#pragma once
#include <Player.hpp>
#include <Enemy.hpp>
#include <memory>
#include <ScreenSize.hpp>
#include <ncurses.h>

enum class BattleTurn {
    PLAYER,
    ENEMY
};

bool startBattle(const ScreenSize* const screen, std::vector<std::vector<Ceil>>& ceils, std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy, BattleTurn type);