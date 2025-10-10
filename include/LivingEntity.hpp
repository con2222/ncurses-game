#pragma once
#include <Entity.hpp>
#include <memory>

class LivingEntity : public Entity, public std::enable_shared_from_this<LivingEntity> {
public:
    LivingEntity(int x, int y, Entity::Type type, int health);
    int getHealth() const override;
protected:
    int health;
};