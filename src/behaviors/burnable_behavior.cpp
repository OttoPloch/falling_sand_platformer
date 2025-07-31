#include "burnable_behavior.hpp"

BurnableBehavior::BurnableBehavior() : Behavior("burnable", -1) {}

BurnableBehavior::BurnableBehavior(int burnability) : Behavior("burnable", burnability) {}

bool BurnableBehavior::update(CellManager* cellManager, sf::Vector2u gridPos)
{
    return false;
}