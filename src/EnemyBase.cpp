#include <EnemyBase.hpp>
#include <random>

EnemyBase::EnemyBase(int x, int y) : LivingEntity(x, y, Entity::Type::ENEMY_BASE, EN_BASE_HP) {}

void EnemyBase::spawnEnemy(std::vector<std::vector<Ceil>>& ceils, std::vector<std::shared_ptr<LivingEntity>>& entities, const ScreenSize* screen, int height, int width) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dis(1, 4);

    int random_number = dis(gen);
    std::shared_ptr<Enemy> enemy_ptr = nullptr;
    if (random_number == 1 && ceils[y - screen->yMax/2 + height/2 + 1][x - screen->xMax/2 + width/2].getEntity()->getType() == Entity::Type::FLOOR) {
        enemy_ptr = std::make_shared<Enemy>(x, y + 1);
        ceils[y - screen->yMax/2 + height/2 + 1][x - screen->xMax/2 + width/2].setEntity(enemy_ptr);
        entities.push_back(enemy_ptr);
    } else if (random_number == 2 && ceils[y - screen->yMax/2 + height/2 - 1][x - screen->xMax/2 + width/2].getEntity()->getType() == Entity::Type::FLOOR) {
        enemy_ptr = std::make_shared<Enemy>(x, y - 1);
        ceils[y - screen->yMax/2 + height/2 - 1][x - screen->xMax/2 + width/2].setEntity(enemy_ptr);
        entities.push_back(enemy_ptr);
    } else if (random_number == 3 && ceils[y - screen->yMax/2 + height/2][x - screen->xMax/2 + width/2 + 1].getEntity()->getType() == Entity::Type::FLOOR) {
        enemy_ptr = std::make_shared<Enemy>(x + 1, y);
        ceils[y - screen->yMax/2 + height/2][x - screen->xMax/2 + width/2 + 1].setEntity(enemy_ptr);
        entities.push_back(enemy_ptr);
    } else if (random_number == 4 && ceils[y - screen->yMax/2 + height/2][x - screen->xMax/2 + width/2 - 1].getEntity()->getType() == Entity::Type::FLOOR) {
        enemy_ptr = std::make_shared<Enemy>(x - 1, y);
        ceils[y - screen->yMax/2 + height/2][x - screen->xMax/2 + width/2 - 1].setEntity(enemy_ptr);
        entities.push_back(enemy_ptr);
    }
}

void EnemyBase::draw() const {
    mvaddch(y, x, sprite);
}