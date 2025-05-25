#include "flowing_behavior.hpp"

FlowingBehavior::FlowingBehavior() : Behavior("flow") {}

bool FlowingBehavior::update(Grid* grid, sf::Vector2u gridPos)
{
    if (gridPos.x > 0 && gridPos.x < grid->getSizeOfRow(gridPos.y) - 1 && grid->at({gridPos.x - 1, gridPos.y}) == nullptr && grid->at({gridPos.x + 1, gridPos.y}) == nullptr)
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
    else if (gridPos.x > 0 && grid->at({gridPos.x - 1, gridPos.y}) == nullptr)
    {
        grid->moveCell(gridPos, {-1, 0});

        return true;
    }
    else if (gridPos.x < grid->getSizeOfRow(gridPos.y) - 1 && grid->at({gridPos.x + 1, gridPos.y}) == nullptr)
    {
        grid->moveCell(gridPos, {1, 0});

        return true;
    }

    return false;
}