#include "burning_behavior.hpp"

#include "../game_classes/cell.hpp"

BurningBehavior::BurningBehavior() : Behavior("burning", -1) {}

BurningBehavior::BurningBehavior(int smokeChance) : Behavior("burning", smokeChance) {}

bool BurningBehavior::update(CellManager* cellManager, sf::Vector2u gridPos)
{
    // if any neighbors have the cooling behavior, destroy this cell
    std::vector<Cell*> neighbors = cellManager->grid->at(gridPos)->getNeighbors();

    if (neighbors.size() > 0)
    {
        for (int i = 0; i < neighbors.size(); i++)
        {
            if (neighbors[i]->hasBehavior("cooling"))
            {
                cellManager->grid->removeCell(gridPos);

                return true;
            }
        }
    }

    if (getRandomInt(999) + 1 <= cellManager->grid->at(gridPos)->getOptionalSetting("burning"))
    {
        cellManager->grid->at(gridPos)->changeType("smoke");

        return true;
    }

    return false;
}