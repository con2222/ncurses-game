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
public:
    Field();
    int getH() const;
    int getW() const;
    void draw() const;
    void setScreen(const ScreenSize* screen);
    void init();
    void spawnPlayer();
    void spawnEnemy();
    
    bool update(int ch);
};