#include <Entity.hpp>
#include <Wall.hpp>
#include <Color.hpp>

Wall::Wall(int x, int y) : Entity(x, y, Entity::Type::WALL) {}

void Wall::draw() const {
    attron(A_BOLD | COLOR_PAIR(static_cast<int>(ColorPair::WALL)));
    mvaddch(y, x, sprite);
    attroff(A_BOLD | COLOR_PAIR(static_cast<int>(ColorPair::WALL)));
}