#include "static_behavior.hpp"

StaticBehavior::StaticBehavior() : Behavior("static", -1) {}

bool StaticBehavior::update(CellManager* cellManager, sf::Vector2u gridPos)
{
    return false;
}