#include "falling_behavior.hpp"

FallingBehavior::FallingBehavior() : Behavior("fall", -1) {}

bool FallingBehavior::update(Grid* grid, sf::Vector2u gridPos)
{
    if (grid->canMoveDistance(gridPos, {0, 1}))
    {
        grid->moveCell(gridPos, {0, 1});
            
        return true;
    }

    return false;
}