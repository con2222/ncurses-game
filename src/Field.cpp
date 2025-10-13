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
#include <Utils.hpp>

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
    int xStart = screen->xMax / 2 - width / 2;
    int yStart = screen->yMax / 2 - height / 2;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                ceils[i][j].setEntity(std::make_shared<Wall>(xStart + j, yStart + i));
            } else {
                ceils[i][j].setEntity(std::make_shared<Floor>(xStart + j, yStart + i));
            }
        }
    }

    if (height > 8 && width > 3) {
        auto enemy_base_ptr = std::make_shared<EnemyBase>(xStart + 2, yStart + 7);
        entities.push_back(enemy_base_ptr);
        ceils[7][2].setEntity(enemy_base_ptr);
    }

    if (height > 8 && width > 11) {
        auto spiked_trap_ptr = std::make_shared<SpikedTrap>(xStart + 10, yStart + 7);
        ceils[7][10].setEntity(spiked_trap_ptr);
    }

    std::vector<std::pair<int, int>> trapPositions = {
        {2, 3},
        {3, 6},
        {4, 9},
        {5, 4},
        {6, 8},
        {8, 5},
        {9, 7}
    };

    for (const auto& pos : trapPositions) {
        int i = pos.first;
        int j = pos.second;

        if (i > 0 && i < height - 1 && j > 0 && j < width - 1) {

            if (!((i == 7 && j == 2) || (i == 7 && j == 10))) {
                ceils[i][j].setEntity(std::make_shared<SpikedTrap>(xStart + j, yStart + i));
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
    printMultiline(screen->yMax - 5, 0, readFileToString("../assets/bar/turn.txt"));
    printNumbers(screen->yMax - 5, 27, turnCounter);
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
                break;
            } else {
                entities.erase(entities.begin() + 0);
                return false;
            }
        }
    }

    if (!player_ptr) return false;

    player_ptr->resetAttackFlag();

    bool playerMadeAction = false;
    if (ch != ERR && !player_ptr->getInTrap()) {
        playerMadeAction = player_ptr->handleInput(ceils, ch, screen, height, width);
    } else {
        if (ch == ' ') {
            player_ptr->unSetInTrap();
        }
    }

    if (playerMadeAction && !player_ptr->getInTrap()) {

        for (int i = 0; i < entities.size(); ) {
            if (entities[i]->getType() == Entity::Type::ENEMY) {
                if (entities[i]->getHealth() > 0) {
                    std::static_pointer_cast<Enemy>(entities[i])->update(ceils, screen, player_ptr, height, width);
                    ++i;
                } else {
                    entities.erase(entities.begin() + i);

                }
            } else {
                ++i;
            }
        }

        for (const auto& entity : entities) {
            if (entity->getType() == Entity::Type::ENEMY_BASE) {
                if (turnCounter % SPAWN_COOLDOWN == 0) {
                    break;
                }
            }
        }

        turnCounter++;
    }

    return true;
}
