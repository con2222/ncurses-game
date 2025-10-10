#include <ncurses.h>
#include <Field.hpp>
#include <Game.hpp>
#include <clocale>

int main() {
    setlocale(LC_ALL, "");
    Game game;
    game.start();
    return 0;
}