#include <BattleLogic.hpp>
#include <Utils.hpp>
#include <Constants.hpp>
#include <Color.hpp>
#include <Floor.hpp>
#include <ncurses.h>
#include <Window.hpp>
#include <chrono> 

void playPlayerAttackAnimation(int y, int x, std::shared_ptr<Player> player) {
    if (player->getMode() == MELEE_MODE) {
        printMultiline(y, x, readFileToString(KNIGHT_ATTACK1));
        refresh();
        napms(1000);

        printMultiline(y, x, readFileToString(KNIGHT_ATTACK2));
        refresh();
        napms(1000);

        printMultiline(y, x, readFileToString(KNIGHT_ATTACK3));
        refresh();
        napms(1000);
    } else {
        printMultiline(y, x, readFileToString(KNIGHT_SHOOT1));
        refresh();
        napms(1000);

        printMultiline(y, x, readFileToString(KNIGHT_SHOOT2));
        refresh();
        napms(1000);
    }
}

bool playEnemyAttackAnimation(const ScreenSize* screen, int y, int x, std::shared_ptr<Enemy> enemy, bool weaponMode) {
    bool blocked = false;

    napms(500);
    if (weaponMode == MELEE_MODE) {
        printMultiline(y, x, readFileToString(GOBLIN_ATTACK1));
        refresh();
        nodelay(stdscr, TRUE);
        auto start_time = std::chrono::steady_clock::now();
        const int BLOCK_WINDOW_MS = 1000;

        while (true) {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count();

            if (elapsed >= BLOCK_WINDOW_MS) break;

            int ch = getch();
            if (ch == 'e' || ch == 'E') {
                blocked = true;

                printMultiline(screen->yMax / 2 + BATTLE_Y_OFFSET, 
                               screen->xMax / 2 + PLAYER_X_OFFSET, 
                               readFileToString(KNIGHT_BLOCK));
                refresh();
                napms(1000);
                break;
            }
            napms(10); 
        }
    } else {
        printMultiline(y, x, readFileToString(GOBLIN_ATTACK1));
        refresh();
        napms(1000);
    }

    int block_y = y - 2;
    int block_x = x + 10;
    if (!blocked) {
        mvprintw(block_y, block_x, "not blocked!");
    } else {
        mvprintw(block_y, block_x, "blocked!");
    }

    printMultiline(y, x, readFileToString(GOBLIN_ATTACK2));
    refresh();
    napms(1000);

    nodelay(stdscr, FALSE);
    return blocked;
}

void drawBattleScreen(const ScreenSize* screen, BattleTurn turn, std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy, const std::vector<std::string>& options, int selected_option, WINDOW* pl_bar, WINDOW* en_bar, WINDOW* act_bar) {
    clear();

    int centerY = screen->yMax / 2;
    int centerX = screen->xMax / 2;

    if (player->getHealth() > 0) {
        if (player->getMode() == MELEE_MODE) {
            printMultiline(centerY + BATTLE_Y_OFFSET, centerX + PLAYER_X_OFFSET, readFileToString(KNIGHT_MELEE_BATTLE));
        } else {
            printMultiline(centerY + BATTLE_Y_OFFSET, centerX + PLAYER_X_OFFSET, readFileToString(KNIGHT_RANGED_BATTLE));
        }
    } else {
        printMultiline(centerY + BATTLE_Y_OFFSET, centerX + PLAYER_X_OFFSET, readFileToString(GRAVE));
    }

    if (enemy->getHealth() > 0) {
        printMultiline(centerY + BATTLE_Y_OFFSET, centerX + ENEMY_X_OFFSET, readFileToString(GOBLIN_BATTLE));
    } else {
        printMultiline(centerY + BATTLE_Y_OFFSET, centerX + ENEMY_X_OFFSET, readFileToString(GRAVE));
    }
    if (turn == BattleTurn::PLAYER) {
        printMultiline(0, centerX - 40 + PLAYER_TURN_X_OFFSET, readFileToString(PLAYER_TURN_TXT));
    } else {
        printMultiline(0, centerX - 40 + ENEMY_TURN_X_OFFSET, readFileToString(ENEMY_TURN_TXT));
    }

    refresh();
    update_battle_windows(pl_bar, en_bar, act_bar, player, enemy, options, selected_option, turn, screen->xMax);
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
                return BattleTurn::PLAYER; 
            } else if (options[selected_option] == "Skip turn") {
                return BattleTurn::ENEMY;
            }
            break;
    }
    return BattleTurn::PLAYER; 
}

BattleTurn handleEnemyTurn(const ScreenSize* screen, std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy, std::vector<std::vector<Ceil>>& ceils, bool& battleIsOver, int& battleResult) {
    refresh();

    bool blocked = playEnemyAttackAnimation(screen, screen->yMax / 2 - 15, screen->xMax / 2 + 13, enemy, player->getMode());

    if (!blocked) {

        player->takeDamage(enemy->attack());

        if (player->getHealth() <= 0) {
            ceils[player->getY() - screen->yMax/2 + FIELD_HEIGHT/2][player->getX() - screen->xMax/2 + FIELD_WIDTH/2].setEntity(std::make_shared<Floor>(player->getX(), player->getY()));
            battleIsOver = true;
            battleResult = 0; 
        }
    } else {

    }

    return BattleTurn::PLAYER; 
}

bool startBattle(const ScreenSize* const screen, std::vector<std::vector<Ceil>>& ceils, std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy, BattleTurn turn) {

    int height = screen->yMax;
    int width = screen->xMax;

    WINDOW* pl_bar = newwin(height / 5, width / 6, 0, 0);
    WINDOW* en_bar = newwin(height / 5, width / 6, 0, width - width / 6);
    WINDOW* act_bar = newwin(height / 5, width / 6, height - height / 5, 0);

    std::vector<std::string> options = {"Attack", "Change weapon", "Skip turn"};
    int selected_option = 0;

    bool battleIsOver = false;
    int battleResult = 0;
    BattleTurn currentTurn = turn;
    drawBattleScreen(screen, currentTurn, player, enemy, options, selected_option, pl_bar, en_bar, act_bar);
    while (!battleIsOver) {
        if (currentTurn == BattleTurn::PLAYER) {
            currentTurn = handlePlayerTurn(screen, player, enemy, ceils, battleIsOver, battleResult, selected_option, options);
        } else {
            currentTurn = handleEnemyTurn(screen, player, enemy, ceils, battleIsOver, battleResult);
        }
        drawBattleScreen(screen, currentTurn, player, enemy, options, selected_option, pl_bar, en_bar, act_bar);
    }

    napms(1500);

    delwin(pl_bar);
    delwin(en_bar);
    delwin(act_bar);
    clear();

    return battleResult == 1; 
}