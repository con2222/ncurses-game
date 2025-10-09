#include <Enemy.hpp>
#include <Floor.hpp>
#include <Color.hpp>
#include <GameLogic.hpp>
#include <Constants.hpp>

Enemy::Enemy(int x, int y) : LivingEntity(x, y, Entity::Type::ENEMY, EN_HEALTH), damage(EN_DAMAGE), sprite(ENEMY) {}

void Enemy::update(std::vector<std::vector<Ceil>>& ceils, const ScreenSize* screen, std::shared_ptr<Player> player, int height, int width) {

    int nextX = x;
    int nextY = y;

    int playerX = player->getX();
    int playerY = player->getY();

    if (x < playerX) {
        nextX++;
    } else if (x > playerX) {
        nextX--;
    } else if (y < playerY) { 
        nextY++;
    } else if (y > playerY) {
        nextY--;
    }

    if (ceils[nextY - screen->yMax/2 + height/2][nextX - screen->xMax/2 + width/2].getEntity()->getType() == Entity::Type::FLOOR) {
        ceils[y - screen->yMax/2 + height/2][x - screen->xMax/2 + width/2].setEntity(std::make_shared<Floor>(x, y));
        x = nextX;
        y = nextY;
        ceils[y - screen->yMax/2 + height/2][x - screen->xMax/2 + width/2].setEntity(shared_from_this());
    } else if (nextX == playerX && nextY == playerY) {
        if (!player->getWasAttacked()) {
            player->setWasAttacked(true);
            player->takeDamage(damage);
            //startBattle(screen, ceils, player, std::static_pointer_cast<Enemy>(shared_from_this()));
        }
    }
}

void Enemy::draw() const {
    attron(COLOR_PAIR(static_cast<int>(ColorPair::ENEMY)));
    mvaddch(y, x, sprite);
    attroff(COLOR_PAIR(static_cast<int>(ColorPair::ENEMY)));
}

void Enemy::takeDamage(int amount) {
    health-=amount;
}

int Enemy::attack() {return damage;}