#include "settling_behavior.hpp"

SettlingBehavior::SettlingBehavior() : Behavior("settle") {}

bool SettlingBehavior::update(Grid* grid, sf::Vector2u gridPos)
{
    if (gridPos.y < grid->getSize() - 1)
    {
        if (gridPos.x > 0 && gridPos.x < grid->getSizeOfRow(gridPos.y) - 1 && grid->at({gridPos.x - 1, gridPos.y + 1}) == nullptr && grid->at({gridPos.x + 1, gridPos.y + 1}) == nullptr)
        {
            if (getRandomInt(1) == 0)
            {
                grid->moveCell(gridPos, {-1, 1});
            }
            else
            {
                grid->moveCell(gridPos, {1, 1});
            }

            return true;
        }
        else if (gridPos.x > 0 && grid->at({gridPos.x - 1, gridPos.y + 1}) == nullptr)
        {
            grid->moveCell(gridPos, {-1, 1});

            return true;
        }
        else if (gridPos.x < grid->getSizeOfRow(gridPos.y) - 1 && grid->at({gridPos.x + 1, gridPos.y + 1}) == nullptr)
        {
            grid->moveCell(gridPos, {1, 1});

            return true;
        }
    }

    return false;
}