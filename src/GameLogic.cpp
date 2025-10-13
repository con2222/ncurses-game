#include <GameLogic.hpp>
#include <Utils.hpp>
#include <Constants.hpp>
#include <Color.hpp>
#include <Floor.hpp>
#include <ncurses.h>
#include <Window.hpp> 

void playPlayerAttackAnimation(int y, int x, std::shared_ptr<Player> player) {
    if (player->getMode() == MELEE_MODE) {
        printMultiline(y, x, readFileToString("../assets/knight/attack1.txt"));
        refresh();
        napms(1000);

        printMultiline(y, x, readFileToString("../assets/knight/attack2.txt"));
        refresh();
        napms(1000);

        printMultiline(y, x, readFileToString("../assets/knight/attack3.txt"));
        refresh();
        napms(1000);
    } else {
        printMultiline(y, x, readFileToString("../assets/knight/shoot1.txt"));
        refresh();
        napms(1000);

        printMultiline(y, x, readFileToString("../assets/knight/shoot2.txt"));
        refresh();
        napms(1000);
    }
}

void playEnemyAttackAnimation(int y, int x, std::shared_ptr<Enemy> enemy) {
    napms(1000);
    printMultiline(y, x, readFileToString("../assets/enemy/goblinAttack1.txt"));
    refresh();
    napms(1000);

    printMultiline(y, x, readFileToString("../assets/enemy/goblinAttack2.txt"));
    refresh();
    napms(1000);
}

void drawBattleScreen(const ScreenSize* screen, BattleTurn turn, std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy, const std::vector<std::string>& options, int selected_option, WINDOW* pl_bar, WINDOW* en_bar, WINDOW* act_bar) {
    clear();

    int yMax = screen->yMax;
    int xMax = screen->xMax;

    if (player->getMode() == MELEE_MODE) {
        printMultiline(yMax / 2 - 15, xMax / 2 - 50, readFileToString("../assets/knight/inBattle.txt"));
    } else {
        printMultiline(yMax / 2 - 15, xMax / 2 - 50, readFileToString("../assets/knight/withBow.txt"));
    }
    printMultiline(yMax / 2 - 15, xMax / 2 + 13, readFileToString("../assets/enemy/goblin.txt"));

    if (turn == BattleTurn::PLAYER) {
        printMultiline(0, xMax / 2 - 40 + 26, readFileToString("../assets/battle/playerTurn.txt"));
    } else {
        printMultiline(0, xMax / 2 - 40 + 24, readFileToString("../assets/battle/enemyTurn.txt"));
    }

    refresh();
    update_battle_windows(pl_bar, en_bar, act_bar, player, enemy, options, selected_option, turn, xMax);
}

BattleTurn handlePlayerTurn(const ScreenSize* screen, std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy, std::vector<std::vector<Ceil>>& ceils, bool& battleIsOver, int& battleResult, int& selected_option, const std::vector<std::string>& options) {
    flushinp();
    int ch = getch(); 
    switch (ch) {
        case KEY_UP:
            if (selected_option > 0) selected_option--;
            break;
        case KEY_DOWN:
            if (selected_option < options.size() - 1) selected_option++;
            break;
        case ENTER:
            if (options[selected_option] == "Attack") {
                napms(1000);
                playPlayerAttackAnimation(screen->yMax / 2 - 15, screen->xMax / 2 - 50, player);

                int damage = player->attack();
                enemy->takeDamage(damage);

                if (enemy->getHealth() <= 0) {
                    ceils[player->getY() - screen->yMax/2 + FIELD_HEIGHT/2][player->getX() - screen->xMax/2 + FIELD_WIDTH/2].setEntity(std::make_shared<Floor>(player->getX(), player->getY()));
                    player->setX(enemy->getX());
                    player->setY(enemy->getY());
                    ceils[enemy->getY() - screen->yMax/2 + FIELD_HEIGHT/2][enemy->getX() - screen->xMax/2 + FIELD_WIDTH/2].setEntity(player);
                    battleIsOver = true;
                    battleResult = 1; 
                }
                return BattleTurn::ENEMY; 
            } else if (options[selected_option] == "Change weapon") {
                player->switchMode();
                return BattleTurn::ENEMY; 
            }
            break;
    }
    return BattleTurn::PLAYER; 
}

BattleTurn handleEnemyTurn(const ScreenSize* screen, std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy, std::vector<std::vector<Ceil>>& ceils, bool& battleIsOver, int& battleResult) {

    refresh();
    playEnemyAttackAnimation(screen->yMax / 2 - 15, screen->xMax / 2 + 13, enemy);

    player->takeDamage(enemy->attack());

    if (player->getHealth() <= 0) {
        ceils[player->getY() - screen->yMax/2 + FIELD_HEIGHT/2][player->getX() - screen->xMax/2 + FIELD_WIDTH/2].setEntity(std::make_shared<Floor>(player->getX(), player->getY()));
        battleIsOver = true;
        battleResult = 0; 
    }

    return BattleTurn::PLAYER; 
}

bool startBattle(const ScreenSize* const screen, std::vector<std::vector<Ceil>>& ceils, std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy, BattleTurn turn) {

    int height = screen->yMax;
    int width = screen->xMax;

    WINDOW* pl_bar = newwin(height / 5, width / 6, 0, 0);
    WINDOW* en_bar = newwin(height / 5, width / 6, 0, width - width / 6);
    WINDOW* act_bar = newwin(height / 5, width / 6, height - height / 5, 0);

    std::vector<std::string> options = {"Attack", "Change weapon"};
    int selected_option = 0;

    bool battleIsOver = false;
    int battleResult = 0;
    BattleTurn currentTurn = turn;

    while (!battleIsOver) {

        drawBattleScreen(screen, currentTurn, player, enemy, options, selected_option, pl_bar, en_bar, act_bar);

        if (currentTurn == BattleTurn::PLAYER) {
            currentTurn = handlePlayerTurn(screen, player, enemy, ceils, battleIsOver, battleResult, selected_option, options);
        } else {
            currentTurn = handleEnemyTurn(screen, player, enemy, ceils, battleIsOver, battleResult);
        }
    }

    delwin(pl_bar);
    delwin(en_bar);
    delwin(act_bar);
    clear();

    return battleResult == 1; 
}