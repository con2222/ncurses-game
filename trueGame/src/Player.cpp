#include <Player.hpp>
#include <Constants.hpp>
#include <Entity.hpp>
#include <Color.hpp>
#include <memory>
#include <Floor.hpp>
#include <GameLogic.hpp>
#include <Enemy.hpp>

Player::Player(int x, int y) : LivingEntity(x, y, Entity::Type::PLAYER, PL_HEALTH), damage(PL_DAMAGE), weaponMode(MELEE_MODE) {}

void Player::handleInput(std::vector<std::vector<Ceil>>& ceils, int ch, const ScreenSize* screen, int height, int width) {
    int nextX = x;
    int nextY = y;

    switch (ch) {
        case UP:
            if (nextY > screen->yMax/2 - height/2 + 1) nextY--;
            break;
        case DOWN:
            if (nextY < screen->yMax/2 + height/2 - 2) nextY++;
            break;
        case LEFT:
            if (nextX > screen->xMax/2 - width/2 + 1) nextX--;
            break;
        case RIGHT:
              if (nextX < screen->xMax/2 + width/2 - 2) nextX++;
            break;
        default:
            break;
    }

    if (ceils[nextY - screen->yMax/2 + height/2][nextX - screen->xMax/2 + width/2].getEntity()->getType() == Entity::Type::FLOOR) {
        ceils[y - screen->yMax/2 + height/2][x - screen->xMax/2 + width/2].setEntity(std::make_shared<Floor>(x, y));
        x = nextX;
        y = nextY;
        ceils[y - screen->yMax/2 + height/2][x - screen->xMax/2 + width/2].setEntity(shared_from_this());
    } else if (ceils[nextY - screen->yMax/2 + height/2][nextX - screen->xMax/2 + width/2].getEntity()->getType() == Entity::Type::ENEMY) {
        wasAttacked = true;
        bool isWin = startBattle(screen, ceils, std::static_pointer_cast<Player>(shared_from_this()), std::static_pointer_cast<Enemy>(ceils[nextY - screen->yMax/2 + height/2][nextX - screen->xMax/2 + width/2].getEntity()));
    }
}

void Player::draw() const {
    mvaddch(y, x, sprite);

    mvprintw(4, 4, "%d", health);
}

void Player::takeDamage(int amount) {
    health-=amount;
}

int Player::attack() {
    return damage;
}

bool Player::getMode() {
    return weaponMode;
}

void Player::switchMode() {
    if (weaponMode == MELEE_MODE) {
        weaponMode = RANGE_MODE;
        damage = RANGE_DAMAGE;
    } else {
        weaponMode = MELEE_MODE;
        damage = MELEE_DAMAGE;
    }
}

void Player::resetAttackFlag() {wasAttacked = false;}

bool Player::getWasAttacked() const {return wasAttacked;}

void Player::setWasAttacked(bool val) {wasAttacked = val;}