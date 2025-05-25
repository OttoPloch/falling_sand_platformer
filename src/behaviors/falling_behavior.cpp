#include "falling_behavior.hpp"

FallingBehavior::FallingBehavior() : Behavior("fall") {}

bool FallingBehavior::update(Grid* grid, sf::Vector2u gridPos)
{
    if (gridPos.y < grid->getSize() - 1)
    {
        if (grid->at({gridPos.x, gridPos.y + 1}) == nullptr)
        {
            grid->moveCell(gridPos, {0, 1});
            
            return true;
        }
    }

    return false;
}