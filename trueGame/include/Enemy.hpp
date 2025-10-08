#pragma once
#include <LivingEntity.hpp>
#include <Constants.hpp>
#include <Player.hpp>
#include <memory>

class Enemy : public LivingEntity {
public:
    Enemy(int x, int y);
    void update(std::vector<std::vector<Ceil>>& ceils, const ScreenSize* screen, std::shared_ptr<Player> player, int height, int width);
    virtual void draw() const override;
    void takeDamage(int amount);
    int attack();

private:
    int damage;
    char sprite;
};