#pragma once
#include <Entity.hpp>

class LivingEntity : public Entity {
public:
    LivingEntity(int x, int y, Entity::Type type, int health);
    int getHealth() const override;
protected:
    int health;
};