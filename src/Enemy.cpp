#include <Enemy.hpp>
#include <Floor.hpp>
#include <Constants.hpp>
#include <cmath>
#include <BattleController.hpp>

Enemy::Enemy(int x, int y) : LivingEntity(x, y, Entity::Type::ENEMY, EN_HEALTH), damage(EN_DAMAGE), sprite(ENEMY) {}

void Enemy::move(std::vector<std::vector<Ceil>>& ceils, const ScreenSize* screen, int newX, int newY, int height, int width) {
    int oldIdxY = y - screen->yMax / 2 + height / 2;
    int oldIdxX = x - screen->xMax / 2 + width / 2;
    ceils[oldIdxY][oldIdxX].setEntity(std::make_shared<Floor>(x, y));

    x = newX;
    y = newY;

    int newIdxY = y - screen->yMax / 2 + height / 2;
    int newIdxX = x - screen->xMax / 2 + width / 2;
    ceils[newIdxY][newIdxX].setEntity(shared_from_this());
}

bool Enemy::isPassable(const std::vector<std::vector<Ceil>>& ceils, const ScreenSize* screen, int nx, int ny, int height, int width) const {
    int idxY = ny - screen->yMax / 2 + height / 2;
    int idxX = nx - screen->xMax / 2 + width / 2;

    if (idxY < 0 || idxY >= static_cast<int>(ceils.size()) ||
        idxX < 0 || idxX >= static_cast<int>(ceils[0].size())) {
        return false;
    }

    auto entity = ceils[idxY][idxX].getEntity();
    return entity && (
        entity->getType() == Entity::Type::FLOOR ||
        entity->getType() == Entity::Type::PLAYER  
    );
}

void Enemy::update(std::vector<std::vector<Ceil>>& ceils, const ScreenSize* screen, std::shared_ptr<Player> player, int height, int width) {
    int playerX = player->getX();
    int playerY = player->getY();

    int dx = (playerX > x) ? 1 : (playerX < x ? -1 : 0);
    int dy = (playerY > y) ? 1 : (playerY < y ? -1 : 0);

    if (abs(x - playerX) <= 1 && abs(y - playerY) <= 1 && !(dx == 0 && dy == 0)) {
        if (!player->getWasAttacked()) {
            player->setWasAttacked(true);
            BattleController battle(screen, ceils, player, std::static_pointer_cast<Enemy>(shared_from_this()), BattleController::BattleTurn::ENEMY);
            int result = battle.start();
        }
        return;
    }

    if (dx != 0 && dy != 0) {

        if (isPassable(ceils, screen, x + dx, y + dy, height, width)) {
            move(ceils, screen, x + dx, y + dy, height, width);
            return;
        }

        if (isPassable(ceils, screen, x + dx, y, height, width)) {
            move(ceils, screen, x + dx, y, height, width);
            return;
        }
        if (isPassable(ceils, screen, x, y + dy, height, width)) {
            move(ceils, screen, x, y + dy, height, width);
            return;
        }
    } else {

        if (dx != 0 && isPassable(ceils, screen, x + dx, y, height, width)) {
            move(ceils, screen, x + dx, y, height, width);
            return;
        }
        if (dy != 0 && isPassable(ceils, screen, x, y + dy, height, width)) {
            move(ceils, screen, x, y + dy, height, width);
            return;
        }
    }

}

void Enemy::draw() const {
    mvaddch(y, x, sprite);
}

void Enemy::takeDamage(int amount) {
    health-=amount;
}

int Enemy::attack() {return damage;}