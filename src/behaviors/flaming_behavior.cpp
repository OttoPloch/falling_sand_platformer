#include "flaming_behavior.hpp"

#include "../game_classes/cell.hpp"

FlamingBehavior::FlamingBehavior() : Behavior("flaming", -1) {}

bool FlamingBehavior::update(CellManager* cellManager, sf::Vector2u gridPos)
{
    std::vector<Cell*> neighbors = cellManager->grid->at(gridPos)->getNeighbors();

    std::vector<Cell*> flammableNeighbors;
    std::vector<Cell*> burnableNeighbors;

    if (neighbors.size() > 0)
    {
        for (int i = 0; i < neighbors.size(); i++)
        {
            if (neighbors[i]->hasBehavior("flammable"))
            {
                flammableNeighbors.emplace_back(neighbors[i]);
            }
            if (neighbors[i]->hasBehavior("burnable"))
            {
                burnableNeighbors.emplace_back(neighbors[i]);
            }
        }
    }

    if (flammableNeighbors.size() > 0)
    {   
        for (int i = 0; i < flammableNeighbors.size(); i++)
        {
            if (getRandomInt(999) + 1 <= flammableNeighbors[i]->getOptionalSetting("flammable"))
            {
                flammableNeighbors[i]->changeType("fire");
            }
        }
    }

    if (burnableNeighbors.size() > 0)
    {   
        for (int i = 0; i < burnableNeighbors.size(); i++)
        {
            if (getRandomInt(999) + 1 <= burnableNeighbors[i]->getOptionalSetting("burnable"))
            {
                cellManager->grid->removeCell(burnableNeighbors[i]->getPosition());
            }
        }
    }

    return false;
}