#include "settling_behavior.hpp"

SettlingBehavior::SettlingBehavior() : Behavior("settle", -1) {}

bool SettlingBehavior::update(CellManager* cellManager, sf::Vector2u gridPos)
{
    int fallDirection;

    if (cellManager->grid->at(gridPos)->getWeight() > 0)
    {
        fallDirection = 1;
    }
    else if (cellManager->grid->at(gridPos)->getWeight() < 0)
    {
        fallDirection = -1;
    }
    else
    {
        std::cout << gridPos.x << ", " << gridPos.y << " of type " << cellManager->grid->at(gridPos)->getType() << " has settle behavior but has a weight of 0\n";
    }

    if ((gridPos.y < cellManager->grid->getSize() - 1 && fallDirection == 1) || (gridPos.y > 0 && fallDirection == -1))
    {
        if (cellManager->grid->canMoveDistance(gridPos, {-1, fallDirection}) && cellManager->grid->canMoveDistance(gridPos, {1, fallDirection}))
        {
            if (getRandomInt(1) == 0)
            {
                cellManager->grid->moveCell(gridPos, {-1, fallDirection});
            }
            else
            {
                cellManager->grid->moveCell(gridPos, {1, fallDirection});
            }

            return true;
        }
        else if (cellManager->grid->canMoveDistance(gridPos, {-1, fallDirection}))
        {
            cellManager->grid->moveCell(gridPos, {-1, fallDirection});

            return true;
        }
        else if (cellManager->grid->canMoveDistance(gridPos, {1, fallDirection}))
        {
            cellManager->grid->moveCell(gridPos, {1, fallDirection});

            return true;
        }
    }

    return false;
}