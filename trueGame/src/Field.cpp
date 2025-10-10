#include "Field.hpp"
#include <ncurses.h>
#include "Color.hpp"
#include <Constants.hpp>
#include <Wall.hpp>
#include <Floor.hpp>
#include <Player.hpp>
#include <Enemy.hpp>
#include <EnemyBase.hpp>
#include <SpikedTrap.hpp>
#include <algorithm>


Field::Field() : screen(nullptr), width(FIELD_WIDTH), height(FIELD_HEIGHT) {
    ceils.resize(height);

    for (int i = 0; i < height; ++i) {
        ceils[i].resize(width);

    }
}

Field::Field(const Field& other) : ceils(other.ceils), entities(other.entities), screen(other.screen), height(other.height), width(other.width) {}

Field::Field(Field&& other) : ceils(std::move(other.ceils)), entities(std::move(other.entities)), screen(other.screen) {
    height = other.height;
    other.height = 0;
    width = other.width;
    other.width = 0;
}

Field& Field::operator=(const Field& other) {
    if (this != &other) {
        ceils = other.ceils;
        entities = other.entities;
        screen = other.screen;
        height = other.height;
        width = other.width;
    }
    return *this;
}

Field& Field::operator=(Field&& other) {
    if (this != &other) {

        ceils = std::move(other.ceils);
        entities = std::move(other.entities);

        screen = other.screen;

        height = other.height;
        width = other.width;

        other.height = 0;
        other.width = 0;
    }
    return *this;
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

            if (i == 7 && j == 2) {
                auto enemy_base_ptr = std::make_shared<EnemyBase>(xStart + j, yStart + i);
                this->entities.push_back(enemy_base_ptr);
                ceils[i][j].setEntity(enemy_base_ptr);
            }

            if (i == 7 && j == 10) {
                auto spiked_trap_ptr = std::make_shared<SpikedTrap>(xStart + j, yStart + i);
                ceils[i][j].setEntity(spiked_trap_ptr);
            }
        }
    }
}



void Field::draw() const { 
    mvprintw(25, 25, "Enemy: %d", entities.size());
    int counter = 0;
    for (const auto i : entities) {
        if (i->getType() == Entity::Type::PLAYER) {
            mvprintw(26 + counter, 25, "Type: Player", entities.size());
            mvprintw(25 + counter, 1, "Player X: %d, Y: %d", i->getX() - screen->xMax/2 + FIELD_WIDTH/2, i->getY() - screen->yMax/2 + FIELD_HEIGHT/2);
            auto player_ptr = std::static_pointer_cast<Player>(i);
            mvprintw(15, 15, "Trapped: %d", player_ptr->getInTrap());
            mvprintw(16, 16, "Weapon mode: %d", player_ptr->getMode()); 
        } else {
            mvprintw(25 + counter, 1, "X: %d, Y: %d", i->getX() - screen->xMax/2 + FIELD_WIDTH/2, i->getY() - screen->yMax/2 + FIELD_HEIGHT/2);
        }
        counter++;
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            ceils[i][j].draw();
        }
    }
}

void Field::setScreen(const ScreenSize* screen) {
    this->screen = screen;
}

void Field::spawnEnemy() {
    int xStart = screen->xMax/2 - width/2;
    int yStart = screen->yMax/2 - height/2;

    auto enemy_ptr = std::make_shared<Enemy>(xStart + 1, yStart + 1);

    this->entities.push_back(enemy_ptr);

    ceils[1][1].setEntity(enemy_ptr);
}

bool Field::update(int ch) { 
    std::shared_ptr<Player> player_ptr = nullptr;
    for (const auto& entity : entities) {
        if (entity->getType() == Entity::Type::PLAYER) {
            if (entity->getHealth() > 0) {
                player_ptr = std::static_pointer_cast<Player>(entity);
                if (ch != ERR) {
                    if (!player_ptr->getInTrap()) {
                        player_ptr->handleInput(ceils, ch, screen, height, width); 
                    } else {
                        player_ptr->unSetInTrap();
                    }
                }
                break; 
            } else {
                entities.erase(entities.begin() + 0);
                return false;
            }
        }
    }

    player_ptr->resetAttackFlag();
    if (player_ptr) {
        for (int i = 0; i < entities.size(); i++) {
            if (entities[i]->getType() == Entity::Type::ENEMY) {
                if (entities[i]->getHealth() > 0) {
                    std::shared_ptr<Enemy> enemy_ptr = std::static_pointer_cast<Enemy>(entities[i]);
                    enemy_ptr->update(ceils, screen, player_ptr, height, width);
                } else {
                    entities.erase(entities.begin() + i);
                }
            }
        }
    }

    /*for (const auto& entity : entities) {
        if (entity->getType() == Entity::Type::ENEMY_BASE) {
            std::static_pointer_cast<EnemyBase>(entity)->spawnEnemy(ceils, entities, screen, height, width);
            break;
        }
    }*/

    return true;
}

