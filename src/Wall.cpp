#include <Entity.hpp>
#include <Wall.hpp>

Wall::Wall(int x, int y) : Entity(x, y, Entity::Type::WALL) {}

void Wall::draw() const {
    mvaddch(y, x, sprite);
}