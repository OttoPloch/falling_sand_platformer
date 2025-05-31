#include "cooling_behavior.hpp"

CoolingBehavior::CoolingBehavior() : Behavior("cooling", -1) {}

bool CoolingBehavior::update(Grid* grid, sf::Vector2u gridPos)
{
    return false;
}