#include <Game.hpp>
#include <Constants.hpp>
#include <Color.hpp>
#include <Wall.hpp>
#include <Floor.hpp>
#include <Menu.hpp>

Game::Game() : field() {}

void Game::initScreen() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    start_color();
    keypad(stdscr, TRUE);
    initGameColors();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    screen = {yMax, xMax};
    field.setScreen(&screen);
}

void Game::cleanup() {
    clear();
    endwin();
}

void Game::start() {
    initScreen();

    bool choice = 0;

    field.init();
    field.spawnPlayer();
    field.spawnEnemy();
    field.draw();
    Menu menu(screen.yMax, screen.xMax);
    choice = menu.init();
    //menu.deinit();
    if (choice) {
        int ch;
        bool playerIsAlive = 1;
        while (true) {
            ch = getch();
            if (ch == 'q') {break;}
            playerIsAlive = field.update(ch);

            if (playerIsAlive == 0) {
                break;
            }
            clear();

            field.draw();

            refresh();
        }
    }
    menu.deinit();
    cleanup();
}