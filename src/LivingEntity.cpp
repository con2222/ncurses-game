#include <LivingEntity.hpp>

LivingEntity::LivingEntity(int x, int y, Entity::Type type, int health) : Entity(x, y, type), health(health) {}

int LivingEntity::getHealth() const {return health;}