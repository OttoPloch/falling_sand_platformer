#include "settling_behavior.hpp"

SettlingBehavior::SettlingBehavior() : Behavior("settle", -1) {}

bool SettlingBehavior::update(Grid* grid, sf::Vector2u gridPos)
{
    int fallDirection;

    if (grid->at(gridPos)->hasBehavior("fall"))
    {
        fallDirection = 1;
    }
    else if (grid->at(gridPos)->hasBehavior("rise"))
    {
        fallDirection = -1;
    }
    else
    {
        std::cout << "Cell at " << gridPos.x << ", " << gridPos.y << " of type " << grid->at(gridPos)->getType() << " has the settle behavior but does not rise or fall\n";
    }

    if ((gridPos.y < grid->getSize() - 1 && fallDirection == 1) || (gridPos.y > 0 && fallDirection == -1))
    {
        if (grid->canMoveDistance(gridPos, {-1, fallDirection}) && grid->canMoveDistance(gridPos, {1, fallDirection}))
        {
            if (getRandomInt(1) == 0)
            {
                grid->moveCell(gridPos, {-1, fallDirection});
            }
            else
            {
                grid->moveCell(gridPos, {1, fallDirection});
            }

            return true;
        }
        else if (grid->canMoveDistance(gridPos, {-1, fallDirection}))
        {
            grid->moveCell(gridPos, {-1, fallDirection});

            return true;
        }
        else if (grid->canMoveDistance(gridPos, {1, fallDirection}))
        {
            grid->moveCell(gridPos, {1, fallDirection});

            return true;
        }
    }

    return false;
}