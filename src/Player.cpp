#include <Player.hpp>
#include <Constants.hpp>
#include <string>
#include <Entity.hpp>
#include <memory>
#include <Floor.hpp>
#include <BattleLogic.hpp>
#include <Enemy.hpp>
#include <Utils.hpp>

Player::Player(int x, int y) : LivingEntity(x, y, Entity::Type::PLAYER, PL_HEALTH), damage(MELEE_DAMAGE), weaponMode(MELEE_MODE) {}

void Player::resetAttackFlag() {wasAttacked = false;}

bool Player::getWasAttacked() const {return wasAttacked;}

void Player::setWasAttacked(bool val) {wasAttacked = val;}

bool Player::getInTrap() {return inTrap;}

void Player::setInTrap() {
    inTrap = true;
}

void Player::unSetInTrap() {
    inTrap = false;
}

bool Player::handleInput(std::vector<std::vector<Ceil>>& ceils, int ch, const ScreenSize* screen, int height, int width) {
    if (ch == SPACE) {return true;}

    int nextX = x;
    int nextY = y;
    bool moved = false;

    switch (ch) {
        case UP:
            if (nextY > screen->yMax/2 - height/2 + 1) {nextY--; moved = true;}
            break;
        case DOWN:
            if (nextY < screen->yMax/2 + height/2 - 2) {nextY++; moved = true;}
            break;
        case LEFT:
            if (nextX > screen->xMax/2 - width/2 + 1) {nextX--; moved = true;}
            break;
        case RIGHT:
            if (nextX < screen->xMax/2 + width/2 - 2) {nextX++; moved = true;}
            break;
        case TAB:
            switchMode();
            napms(200);
            flushinp();
            return true;
        default:
            return false;
    }

    if (!moved) {
        return false;
    }

    auto& targetCell = ceils[nextY - screen->yMax/2 + height/2][nextX - screen->xMax/2 + width/2];
    auto targetType = targetCell.getEntity()->getType();

    if (targetType == Entity::Type::FLOOR) {
        ceils[y - screen->yMax/2 + height/2][x - screen->xMax/2 + width/2].setEntity(std::make_shared<Floor>(x, y));
        x = nextX;
        y = nextY;
        ceils[y - screen->yMax/2 + height/2][x - screen->xMax/2 + width/2].setEntity(shared_from_this());
        return true;
    } else if (targetType == Entity::Type::ENEMY) {
        wasAttacked = true;
        startBattle(screen, ceils, std::static_pointer_cast<Player>(shared_from_this()),
                    std::static_pointer_cast<Enemy>(targetCell.getEntity()), BattleTurn::PLAYER);
        return true;
    } else if (targetType == Entity::Type::SPIKED_TRAP) {
        setInTrap();
        ceils[y - screen->yMax/2 + height/2][x - screen->xMax/2 + width/2].setEntity(std::make_shared<Floor>(x, y));
        x = nextX;
        y = nextY;
        ceils[y - screen->yMax/2 + height/2][x - screen->xMax/2 + width/2].setEntity(shared_from_this());
        return true;
    }

    return false;
}

void Player::draw() const {
    mvaddch(y, x, sprite);
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);
    
    printMultiline(0, 0, readFileToString(KNIGHT));
    printMultiline(0, 32, readFileToString(HP));
    printNumbers(0, 47, health);
    printMultiline(5, 32, readFileToString(DMG));
    printNumbers(5, 54, damage);
    if (weaponMode == MELEE_MODE) {
        printMultiline(0, xMax - 30, readFileToString(SWORD));
    } else {
        printMultiline(0, xMax - 30, readFileToString(BOW));
    }
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