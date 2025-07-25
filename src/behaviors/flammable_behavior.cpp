#include "flammable_behavior.hpp"

FlammableBehavior::FlammableBehavior() : Behavior("flammable", -1) {}

FlammableBehavior::FlammableBehavior(int flammability) : Behavior("flammable", flammability) {}

bool FlammableBehavior::update(CellManager* cellManager, sf::Vector2u gridPos)
{
    return false;
}