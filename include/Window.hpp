#pragma once
#include <ncurses.h>
#include <memory>
#include <vector>
#include <string>
#include <GameLogic.hpp>

class Player;
class Enemy;

WINDOW* create_player_bar(int height, int width);
WINDOW* create_enemy_bar(int height, int width);
WINDOW* create_action_bar(int height, int width);

void draw_player_bar(WINDOW* pl_bar, WINDOW* en_bar, WINDOW* act_bar, int width);
void update_battle_windows(
    WINDOW* pl_bar, WINDOW* en_bar, WINDOW* act_bar,
    std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy,
    const std::vector<std::string>& options, int selected_option,
    BattleTurn turn, int width
);
