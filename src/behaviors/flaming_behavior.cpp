#include "flaming_behavior.hpp"

#include "../game_classes/cell.hpp"

FlamingBehavior::FlamingBehavior() : Behavior("flaming", -1) {}

bool FlamingBehavior::update(CellManager* cellManager, sf::Vector2u gridPos)
{
    std::vector<sf::Vector2i> flammableNeighbors;

    if (gridPos.x > 0 && gridPos.y > 0 && cellManager->grid->at({gridPos.x - 1, gridPos.y - 1}) != nullptr && cellManager->grid->at({gridPos.x - 1, gridPos.y - 1})->hasBehavior("flammable")) { flammableNeighbors.push_back({-1, -1}); }
    if (gridPos.y > 0 && cellManager->grid->at({gridPos.x, gridPos.y - 1}) != nullptr && cellManager->grid->at({gridPos.x, gridPos.y - 1})->hasBehavior("flammable")) { flammableNeighbors.push_back({0, -1}); }
    if (gridPos.x < cellManager->grid->getLength() - 1 && gridPos.y > 0 && cellManager->grid->at({gridPos.x + 1, gridPos.y - 1}) != nullptr && cellManager->grid->at({gridPos.x + 1, gridPos.y - 1})->hasBehavior("flammable")) { flammableNeighbors.push_back({1, -1}); }
    if (gridPos.x > 0 && cellManager->grid->at({gridPos.x - 1, gridPos.y}) != nullptr && cellManager->grid->at({gridPos.x - 1, gridPos.y})->hasBehavior("flammable")) { flammableNeighbors.push_back({-1, 0}); }
    if (gridPos.x < cellManager->grid->getLength() - 1 && cellManager->grid->at({gridPos.x + 1, gridPos.y}) != nullptr && cellManager->grid->at({gridPos.x + 1, gridPos.y})->hasBehavior("flammable")) { flammableNeighbors.push_back({1, 0}); }
    if (gridPos.x > 0 && gridPos.y < cellManager->grid->getHeight() - 1 && cellManager->grid->at({gridPos.x - 1, gridPos.y + 1}) != nullptr && cellManager->grid->at({gridPos.x - 1, gridPos.y + 1})->hasBehavior("flammable")) { flammableNeighbors.push_back({-1, 1}); }
    if (gridPos.y < cellManager->grid->getHeight() - 1 && cellManager->grid->at({gridPos.x, gridPos.y + 1}) != nullptr && cellManager->grid->at({gridPos.x, gridPos.y + 1})->hasBehavior("flammable")) { flammableNeighbors.push_back({0, 1}); }
    if (gridPos.x < cellManager->grid->getLength() - 1 && gridPos.y < cellManager->grid->getHeight() - 1 && cellManager->grid->at({gridPos.x + 1, gridPos.y + 1}) != nullptr && cellManager->grid->at({gridPos.x + 1, gridPos.y + 1})->hasBehavior("flammable")) { flammableNeighbors.push_back({1, 1}); }

    if (flammableNeighbors.size() > 0)
    {   
        for (int i = 0; i < flammableNeighbors.size(); i++)
        {
            if (getRandomInt(999) + 1 <= cellManager->grid->at({gridPos.x + flammableNeighbors[i].x, gridPos.y + flammableNeighbors[i].y})->getOptionalSetting("flammable"))
            {
                cellManager->grid->at({gridPos.x + flammableNeighbors[i].x, gridPos.y + flammableNeighbors[i].y})->changeType("fire");
            }
        }
    }

    return false;
}