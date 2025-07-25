#include "cooling_behavior.hpp"

CoolingBehavior::CoolingBehavior() : Behavior("cooling", -1) {}

bool CoolingBehavior::update(CellManager* cellManager, sf::Vector2u gridPos)
{
    return false;
}