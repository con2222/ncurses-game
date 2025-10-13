#include <Game.hpp>
#include <Constants.hpp>
#include <Color.hpp>
#include <Wall.hpp>
#include <Floor.hpp>
#include <Menu.hpp>
#include <iostream>

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

bool Game::help() {
    std::cout << "\n";
    std::cout << "=============================================\n";
    std::cout << "            ДОБРО ПОЖАЛОВАТЬ В ИГРУ!\n";
    std::cout << "=============================================\n\n";

    std::cout << "Перед запуском убедитесь, что:\n";
    std::cout << "  • Размер шрифта терминала — не более 12pt\n";
    std::cout << "  • Окно терминала развернуто на весь экран\n\n";

    std::cout << "УПРАВЛЕНИЕ:\n";
    std::cout << "  Стрелки — движение по локации\n";
    std::cout << "  TAB     — сменить оружие (ближний/дальний бой)\n";
    std::cout << "  Пробел  — пропустить ход / выбраться из ловушки\n";
    std::cout << "  Q       — выйти из игры\n";
    std::cout << "  E       — заблокировать удар во время боя\n\n";

    std::cout << "Чтобы начать игру, введите:  start\n";
    std::cout << "Чтобы выйти, введите:        exit\n";
    std::cout << "\n";

    std::string command;

    while (true) {
        std::cout << ">>>";
        std::getline(std::cin, command);

        if (command == "start") {
            break;
        } else if (command == "exit") {
            std::cout << "Выход из игры.\n";
            return 0;
        } else {
            std::cout << "\nНеизвестная команда. Введите 'start' или 'exit'.\n";
        }
    }
    return 1;
}

void Game::start() {
    initScreen();

    bool choice = 0;


    Menu menu(screen.yMax, screen.xMax);
    choice = menu.init();

    if (choice) {
        field.init();
        field.spawnPlayer();
        field.draw();
        int ch;
        bool playerIsAlive = 1;
        while (true) {
            ch = getch();
            if (ch == 'q') {break;}
            playerIsAlive = field.update(ch);

            if (playerIsAlive == 0) {
                clear();
                refresh();
                menu.gameOver();
                break;
            }
            clear();

            field.draw();

            refresh();
        }
    }
    cleanup();
}