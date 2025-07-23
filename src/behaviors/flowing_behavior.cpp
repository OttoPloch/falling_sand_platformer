#include "flowing_behavior.hpp"

FlowingBehavior::FlowingBehavior() : Behavior("flow", -1) {}

bool FlowingBehavior::update(Grid* grid, sf::Vector2u gridPos)
{
    if (grid->canMoveDistance(gridPos, {-1, 0}) && grid->canMoveDistance(gridPos, {1, 0}))
    {
        if (getRandomInt(1) == 0)
        {
            grid->moveCell(gridPos, {-1, 0});
        }
        else
        {
            grid->moveCell(gridPos, {1, 0});
        }

        return true;
    }
    else if (grid->canMoveDistance(gridPos, {-1, 0}))
    {
        grid->moveCell(gridPos, {-1, 0});

        return true;
    }
    else if (grid->canMoveDistance(gridPos, {1, 0}))
    {
        grid->moveCell(gridPos, {1, 0});

        return true;
    }

    return false;
}