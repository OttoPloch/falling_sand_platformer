#include "flowing_behavior.hpp"

FlowingBehavior::FlowingBehavior() : Behavior("flow", -1) {}

bool FlowingBehavior::update(CellManager* cellManager, sf::Vector2u gridPos)
{
    if (cellManager->grid->canMoveDistance(gridPos, {-1, 0}) && cellManager->grid->canMoveDistance(gridPos, {1, 0}))
    {
        if (getRandomInt(1) == 0)
        {
            cellManager->grid->moveCell(gridPos, {-1, 0});
        }
        else
        {
            cellManager->grid->moveCell(gridPos, {1, 0});
        }

        return true;
    }
    else if (cellManager->grid->canMoveDistance(gridPos, {-1, 0}))
    {
        cellManager->grid->moveCell(gridPos, {-1, 0});

        return true;
    }
    else if (cellManager->grid->canMoveDistance(gridPos, {1, 0}))
    {
        cellManager->grid->moveCell(gridPos, {1, 0});

        return true;
    }

    return false;
}