#include "flowing_behavior.hpp"

#include "../game_classes/cell.hpp"

FlowingBehavior::FlowingBehavior() : Behavior("flow", -1) {}

FlowingBehavior::FlowingBehavior(int flowChance) : Behavior("flow", flowChance) {}

bool FlowingBehavior::update(CellManager* cellManager, sf::Vector2u gridPos)
{
    if (cellManager->grid->canMoveDistance(gridPos, {-1, 0}) && cellManager->grid->canMoveDistance(gridPos, {1, 0}))
    {
        if (getRandomBalancedInt(999) + 1 <= cellManager->grid->at(gridPos)->getOptionalSetting("flow"))
        {
            if (getRandomInt(1) == 0)
            {
                cellManager->grid->moveCell(gridPos, {-1, 0});
            }
            else
            {
                cellManager->grid->moveCell(gridPos, {1, 0});
            }
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