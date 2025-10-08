#include "Field.hpp"
#include <ncurses.h>
#include "Color.hpp"
#include <Constants.hpp>
#include <Wall.hpp>
#include <Floor.hpp>
#include <Player.hpp>
#include <Enemy.hpp>
#include <algorithm>


Field::Field() : screen(nullptr), width(FIELD_WIDTH), height(FIELD_HEIGHT) {
    ceils.resize(height);

    for (int i = 0; i < height; ++i) {
        ceils[i].resize(width);

    }
}

void Field::init() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int xStart = screen->xMax/2 - width/2;
            int yStart = screen->yMax/2 - height/2;
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                ceils[i][j].setEntity(std::make_shared<Wall>(xStart + j, yStart + i));
            } else {
                ceils[i][j].setEntity(std::make_shared<Floor>(xStart + j, yStart + i));
            }
        }
    }
}



void Field::draw() const { 
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            ceils[i][j].draw();
        }
    }
}

void Field::setScreen(const ScreenSize* screen) {
    this->screen = screen;
}

void Field::spawnPlayer() {
    int xStart = screen->xMax/2 - width/2;
    int yStart = screen->yMax/2 - height/2;
    int playerX = xStart + width/2;
    int playerY = yStart + height/2;

    auto player_ptr = std::make_shared<Player>(playerX, playerY);

    this->entities.push_back(player_ptr);

    ceils[height/2][width/2].setEntity(player_ptr);
}

void Field::spawnEnemy() {
    int xStart = screen->xMax/2 - width/2;
    int yStart = screen->yMax/2 - height/2;

    auto enemy_ptr = std::make_shared<Enemy>(xStart + 1, yStart + 1);

    this->entities.push_back(enemy_ptr);

    ceils[1][1].setEntity(enemy_ptr);
}

void Field::update(int ch) { 
    std::shared_ptr<Player> player_ptr = nullptr;
    for (const auto& entity : entities) {
        if (entity->getType() == Entity::Type::PLAYER) {
            player_ptr = std::static_pointer_cast<Player>(entity);
            if (ch != ERR) {
                 player_ptr->handleInput(ceils, ch, screen, height, width); 
            }
            break; 
        }
    }

    if (player_ptr) {
        for (const auto& entity : entities) {
            if (entity->getType() == Entity::Type::ENEMY) {
                if (entity->getHealth() > 0) {
                    std::shared_ptr<Enemy> enemy_ptr = std::static_pointer_cast<Enemy>(entity);
                    enemy_ptr->update(ceils, screen, player_ptr, height, width);
                }
            }
        }
    }

    auto it_to_remove = std::remove_if(entities.begin(), entities.end(), 
        [](const std::shared_ptr<Entity>& entity) {
            // Возвращаем true, если сущность нужно удалить
            return entity->getHealth() <= 0;
        }
    );

    bool player_is_alive = false;
    for (const auto& entity : entities) {
        if (entity->getType() == Entity::Type::PLAYER) {
            player_is_alive = true;
            break;
        }
    }

    if (!player_is_alive) {
        // Здесь можно установить флаг game_over или вызвать соответствующий метод
    }
}
