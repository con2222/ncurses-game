#pragma once
#include <Entity.hpp>
#include <Ceil.hpp>
#include <Constants.hpp>
#include <vector>
#include <LivingEntity.hpp>

class Player : public LivingEntity {
public:
    Player(int x, int y);
    
    void handleInput(std::vector<std::vector<Ceil>>& ceils, int ch, const ScreenSize* screen, int height, int width);
    int attack();
    virtual void draw() const override;
    void takeDamage(int amount);
    void resetAttackFlag();
    bool getWasAttacked() const;
    void setWasAttacked(bool val);
    bool getInTrap();
    void setInTrap();
    void unSetInTrap();
    void switchMode();
    bool getMode();
private:
    int damage;
    bool weaponMode;
    bool wasAttacked = false;
    bool inTrap = false;
    char sprite = PLAYER;
}; 
