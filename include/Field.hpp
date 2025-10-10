#pragma once
#include <Ceil.hpp>
#include <vector>
#include <ScreenSize.hpp>
#include <memory>
#include <LivingEntity.hpp>

class Field {
    std::vector<std::vector<Ceil>> ceils;
    std::vector<std::shared_ptr<LivingEntity>> entities;
    const ScreenSize* screen;
    int height;
    int width;
    size_t turnCounter;
public:
    Field();
    Field(const Field& other);
    Field(Field&& other);
    Field& operator=(const Field& other);
    Field& operator=(Field&& other);


    int getH() const;
    int getW() const;
    void draw() const;
    void setScreen(const ScreenSize* screen);
    void init();
    void spawnPlayer();
    void spawnEnemy();
    
    bool update(int ch);
};