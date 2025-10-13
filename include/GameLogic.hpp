#pragma once

#include <Player.hpp>
#include <Enemy.hpp>
#include <memory>
#include <vector>
#include <string>
#include <ScreenSize.hpp>
#include <ncurses.h>

class Ceil;

enum class BattleTurn {
    PLAYER,
    ENEMY
};

bool startBattle(const ScreenSize* const screen, std::vector<std::vector<Ceil>>& ceils, std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy, BattleTurn turn);

void playPlayerAttackAnimation(int y, int x);

void drawBattleScreen(const ScreenSize* screen, BattleTurn turn, std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy, const std::vector<std::string>& options, int selected_option, WINDOW* pl_bar, WINDOW* en_bar, WINDOW* act_bar);

BattleTurn handlePlayerTurn(const ScreenSize* screen, std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy, std::vector<std::vector<Ceil>>& ceils, bool& battleIsOver, int& battleResult, int& selected_option, const std::vector<std::string>& options);

BattleTurn handleEnemyTurn(const ScreenSize* screen, std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy, std::vector<std::vector<Ceil>>& ceils, bool& battleIsOver, int& battleResult);