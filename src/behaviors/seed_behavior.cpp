#include "seed_behavior.hpp"

#include "../game_classes/cell.hpp"
#include "planted_behavior.hpp"

SeedBehavior::SeedBehavior() : Behavior("seed", -1) {}

SeedBehavior::SeedBehavior(int waterToSprout) : Behavior("seed", waterToSprout) {}

bool SeedBehavior::update(CellManager* cellManager, sf::Vector2u gridPos)
{
    if (!cellManager->grid->at(gridPos)->hasBehavior("planted"))
    {
        if (cellManager->grid->at({gridPos.x, gridPos.y + 1}) != nullptr && cellManager->grid->at({gridPos.x, gridPos.y + 1})->getType() == "soil")
        {
            cellManager->grid->at(gridPos)->addEndBehavior(std::make_shared<PlantedBehavior>());
        }
    }
    else
    {
        // if any neighbors are water, absorb it and add to waterLevel
        if (gridPos.x > 0 && gridPos.y > 0 && cellManager->grid->at({gridPos.x - 1, gridPos.y - 1}) != nullptr && cellManager->grid->at({gridPos.x - 1, gridPos.y - 1})->getType() == "water") { cellManager->grid->removeCell({gridPos.x - 1, gridPos.y - 1}); cellManager->grid->at(gridPos)->addToWaterLevel(1); }
        if (gridPos.y > 0 && cellManager->grid->at({gridPos.x, gridPos.y - 1}) != nullptr && cellManager->grid->at({gridPos.x, gridPos.y - 1})->getType() == "water") { cellManager->grid->removeCell({gridPos.x, gridPos.y - 1}); cellManager->grid->at(gridPos)->addToWaterLevel(1); }
        if (gridPos.x < cellManager->grid->getLength() - 1 && gridPos.y > 0 && cellManager->grid->at({gridPos.x + 1, gridPos.y - 1}) != nullptr && cellManager->grid->at({gridPos.x + 1, gridPos.y - 1})->getType() == "water") { cellManager->grid->removeCell({gridPos.x + 1, gridPos.y - 1}); }
        if (gridPos.x > 0 && cellManager->grid->at({gridPos.x - 1, gridPos.y}) != nullptr && cellManager->grid->at({gridPos.x - 1, gridPos.y})->getType() == "water") { cellManager->grid->removeCell({gridPos.x - 1, gridPos.y}); cellManager->grid->at(gridPos)->addToWaterLevel(1); }
        if (gridPos.x < cellManager->grid->getLength() - 1 && cellManager->grid->at({gridPos.x + 1, gridPos.y}) != nullptr && cellManager->grid->at({gridPos.x + 1, gridPos.y})->getType() == "water") { cellManager->grid->removeCell({gridPos.x + 1, gridPos.y}); cellManager->grid->at(gridPos)->addToWaterLevel(1); }
        if (gridPos.x > 0 && gridPos.y < cellManager->grid->getHeight() - 1 && cellManager->grid->at({gridPos.x - 1, gridPos.y + 1}) != nullptr && cellManager->grid->at({gridPos.x - 1, gridPos.y + 1})->getType() == "water") { cellManager->grid->removeCell({gridPos.x - 1, gridPos.y + 1}); cellManager->grid->at(gridPos)->addToWaterLevel(1); }
        if (gridPos.y < cellManager->grid->getHeight() - 1 && cellManager->grid->at({gridPos.x, gridPos.y + 1}) != nullptr && cellManager->grid->at({gridPos.x, gridPos.y + 1})->getType() == "water") { cellManager->grid->removeCell({gridPos.x, gridPos.y + 1}); cellManager->grid->at(gridPos)->addToWaterLevel(1); }
        if (gridPos.x < cellManager->grid->getLength() - 1 && gridPos.y < cellManager->grid->getHeight() - 1 && cellManager->grid->at({gridPos.x + 1, gridPos.y + 1}) != nullptr && cellManager->grid->at({gridPos.x + 1, gridPos.y + 1})->getType() == "water") { cellManager->grid->removeCell({gridPos.x + 1, gridPos.y + 1}); cellManager->grid->at(gridPos)->addToWaterLevel(1); }
    
        if (cellManager->grid->at(gridPos)->getWaterLevel() >= cellManager->grid->at(gridPos)->getOptionalSetting("seed"))
        {
            cellManager->grid->at(gridPos)->changeType("stem");

            cellManager->grid->at(gridPos)->addEndBehavior(std::make_shared<PlantedBehavior>());

            return true;
        }
    }

    return false;
}