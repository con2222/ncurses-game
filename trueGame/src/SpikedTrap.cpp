#include <SpikedTrap.hpp>

SpikedTrap::SpikedTrap(int x, int y) : Entity(x, y, Entity::Type::SPIKED_TRAP) {}

void SpikedTrap::draw() const {
    mvaddch(y, x, sprite);
}