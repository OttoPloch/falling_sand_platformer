#include "flammable_behavior.hpp"

FlammableBehavior::FlammableBehavior() : Behavior("flammable", -1) {}

FlammableBehavior::FlammableBehavior(int flammability) : Behavior("flammable", flammability) {}

bool FlammableBehavior::update(Grid* grid, sf::Vector2u gridPos)
{
    return false;
}