#include <GameLogic.hpp>
#include <Utils.hpp>
#include <Constants.hpp>
#include <Color.hpp>
#include <Floor.hpp>
#include <ncurses.h>
#include <Window.hpp>

void draw(int yMax, int xMax, BattleTurn turn) {
    clear();
    printMultiline(0, xMax/2 - 40, readFileToString("../assets/battle/turnBar.txt"));
    if (turn == BattleTurn::PLAYER) {
        printMultiline(3, xMax/2 - 40 + 26, readFileToString("../assets/battle/playerTurn.txt"));
    } else {
        printMultiline(3, xMax/2 - 40 + 24, readFileToString("../assets/battle/enemyTurn.txt"));
    }
    refresh();
}

bool startBattle(const ScreenSize* const screen, std::vector<std::vector<Ceil>>& ceils, std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy, BattleTurn turn) {
    clear();

    int height = screen->yMax;
    int width = screen->xMax;

    WINDOW* pl_bar = create_player_bar(height, width);
    WINDOW* en_bar = create_enemy_bar(height, width);
    WINDOW* act_bar = create_action_bar(height, width);

    refresh();
    wrefresh(pl_bar);
    wrefresh(en_bar);
    wrefresh(act_bar);

    std::vector<std::string> options {"Attack", "Change weapon"};
    int selected_option = 0;
    int ch = 0;

    bool battleIsOver = false;
    BattleTurn currentTurn = turn;
    int battleResult = 0;

    update_battle_windows(pl_bar, en_bar, act_bar, player, enemy, options, selected_option, turn, width);

    while(!battleIsOver) {
        draw(screen->yMax, screen->xMax, currentTurn);
        update_battle_windows(pl_bar, en_bar, act_bar, player, enemy, options, selected_option, turn, width);
        if (currentTurn == BattleTurn::PLAYER) {
            int ch = getch();
            switch (ch) {
                case KEY_UP:
                    if (selected_option > 0) {
                        selected_option--;
                    }
                    break;
                case KEY_DOWN:
                    if (selected_option < 1) {
                        selected_option++;
                    }
                    break;
                case ENTER:
                    if (options[selected_option] == "Attack") {
                        napms(500);
                        int damage = player->attack();
                        enemy->takeDamage(damage);



                        if (enemy->getHealth() <= 0) {
                            ceils[player->getY() - screen->yMax/2 + FIELD_HEIGHT/2][player->getX() - screen->xMax/2 + FIELD_WIDTH/2].setEntity(std::make_shared<Floor>(player->getX(), player->getY()));
                            player->setX(enemy->getX());
                            player->setY(enemy->getY());
                            ceils[enemy->getY() - screen->yMax/2 + FIELD_HEIGHT/2][enemy->getX() - screen->xMax/2 + FIELD_WIDTH/2].setEntity(player);
                            battleIsOver = true;
                            battleResult = 1;
                        } else {
                            currentTurn = BattleTurn::ENEMY;
                        }
                    } else if (options[selected_option] == "Change weapon") {
                        player->switchMode();
                        currentTurn = BattleTurn::ENEMY;
                    }
                    break;
            }
        } else if (currentTurn == BattleTurn::ENEMY) {
            mvprintw(26, 25, "Enemy turn");
            napms(500);
            player->takeDamage(enemy->attack());

            if (player->getHealth() <= 0) {
                ceils[player->getY() - screen->yMax/2 + FIELD_HEIGHT/2][player->getX() - screen->xMax/2 + FIELD_WIDTH/2].setEntity(std::make_shared<Floor>(player->getX(), player->getY()));
                battleIsOver = true;
                battleResult = 0;
            } else {
                currentTurn = BattleTurn::PLAYER;
            }
        }
        update_battle_windows(pl_bar, en_bar, act_bar, player, enemy, options, selected_option, currentTurn, width);
    }
    delwin(pl_bar);
    delwin(en_bar);
    delwin(act_bar);

    return battleResult;
}
