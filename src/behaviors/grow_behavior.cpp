#include "grow_behavior.hpp"

#include "../game_classes/cell.hpp"

GrowBehavior::GrowBehavior() : Behavior("grow", -1) {}

GrowBehavior::GrowBehavior(int waterToGrow) : Behavior("grow", waterToGrow) {}

bool GrowBehavior::update(CellManager* cellManager, sf::Vector2u gridPos)
{
    // if any neighbors are water, absorb it and add to waterLevel
    if (gridPos.x > 0 && gridPos.y > 0 && cellManager->grid->at({gridPos.x - 1, gridPos.y - 1}) != nullptr && cellManager->grid->at({gridPos.x - 1, gridPos.y - 1})->getType() == "water") { cellManager->grid->removeCell({gridPos.x - 1, gridPos.y - 1}); cellManager->grid->at(gridPos)->addToWaterLevel(1); }
    if (gridPos.y > 0 && cellManager->grid->at({gridPos.x, gridPos.y - 1}) != nullptr && cellManager->grid->at({gridPos.x, gridPos.y - 1})->getType() == "water") { cellManager->grid->removeCell({gridPos.x, gridPos.y - 1}); cellManager->grid->at(gridPos)->addToWaterLevel(1); }
    if (gridPos.x < cellManager->grid->getLength() - 1 && gridPos.y > 0 && cellManager->grid->at({gridPos.x + 1, gridPos.y - 1}) != nullptr && cellManager->grid->at({gridPos.x + 1, gridPos.y - 1})->getType() == "water") { cellManager->grid->removeCell({gridPos.x + 1, gridPos.y - 1}); cellManager->grid->at(gridPos)->addToWaterLevel(1); }
    if (gridPos.x > 0 && cellManager->grid->at({gridPos.x - 1, gridPos.y}) != nullptr && cellManager->grid->at({gridPos.x - 1, gridPos.y})->getType() == "water") { cellManager->grid->removeCell({gridPos.x - 1, gridPos.y}); cellManager->grid->at(gridPos)->addToWaterLevel(1); }
    if (gridPos.x < cellManager->grid->getLength() - 1 && cellManager->grid->at({gridPos.x + 1, gridPos.y}) != nullptr && cellManager->grid->at({gridPos.x + 1, gridPos.y})->getType() == "water") { cellManager->grid->removeCell({gridPos.x + 1, gridPos.y}); cellManager->grid->at(gridPos)->addToWaterLevel(1); }
    if (gridPos.x > 0 && gridPos.y < cellManager->grid->getHeight() - 1 && cellManager->grid->at({gridPos.x - 1, gridPos.y + 1}) != nullptr && cellManager->grid->at({gridPos.x - 1, gridPos.y + 1})->getType() == "water") { cellManager->grid->removeCell({gridPos.x - 1, gridPos.y + 1}); cellManager->grid->at(gridPos)->addToWaterLevel(1); }
    if (gridPos.y < cellManager->grid->getHeight() - 1 && cellManager->grid->at({gridPos.x, gridPos.y + 1}) != nullptr && cellManager->grid->at({gridPos.x, gridPos.y + 1})->getType() == "water") { cellManager->grid->removeCell({gridPos.x, gridPos.y + 1}); cellManager->grid->at(gridPos)->addToWaterLevel(1); }
    if (gridPos.x < cellManager->grid->getLength() - 1 && gridPos.y < cellManager->grid->getHeight() - 1 && cellManager->grid->at({gridPos.x + 1, gridPos.y + 1}) != nullptr && cellManager->grid->at({gridPos.x + 1, gridPos.y + 1})->getType() == "water") { cellManager->grid->removeCell({gridPos.x + 1, gridPos.y + 1}); cellManager->grid->at(gridPos)->addToWaterLevel(1); }
    
    if (cellManager->grid->at(gridPos)->getWaterLevel() >= cellManager->grid->at(gridPos)->getOptionalSetting("grow"))
    {
        std::vector<sf::Vector2u> openSpots;

        if (gridPos.x > 0 && cellManager->grid->at({gridPos.x - 1, gridPos.y}) == nullptr) { openSpots.emplace_back(gridPos.x - 1, gridPos.y); }
        if (gridPos.y > 0 && cellManager->grid->at({gridPos.x, gridPos.y - 1}) == nullptr) { openSpots.emplace_back(gridPos.x, gridPos.y - 1); }
        if (gridPos.x < cellManager->grid->getLength() - 1 && cellManager->grid->at({gridPos.x + 1, gridPos.y}) == nullptr) { openSpots.emplace_back(gridPos.x + 1, gridPos.y); }

        if (openSpots.size() > 0)
        {
            // most preferred spots

            // copy this cell to one of the open spots (grow)

            int index = getRandomInt(openSpots.size() - 1);

            cellManager->grid->createCell(cellManager->grid->at(gridPos)->getType(), openSpots[index]);

            cellManager->grid->at(gridPos)->removeBehavior("grow");

            return true;
        }
        else
        {
            if (gridPos.x > 0 && gridPos.y > 0 && cellManager->grid->at({gridPos.x - 1, gridPos.y - 1}) == nullptr) { openSpots.emplace_back(gridPos.x - 1, gridPos.y - 1); }
            if (gridPos.x < cellManager->grid->getLength() - 1 && gridPos.y > 0 && cellManager->grid->at({gridPos.x + 1, gridPos.y - 1}) == nullptr) { openSpots.emplace_back(gridPos.x + 1, gridPos.y - 1); }

            if (openSpots.size() > 0)
            {
                // next preffered

                // copy this cell to one of the open spots (grow)
    
                int index = getRandomInt(openSpots.size() - 1);

                cellManager->grid->createCell(cellManager->grid->at(gridPos)->getType(), openSpots[index]);

                cellManager->grid->at(gridPos)->removeBehavior("grow");
                
                return true;
            }
            else
            {
                if (gridPos.x > 0 && gridPos.y < cellManager->grid->getHeight() - 1 && cellManager->grid->at({gridPos.x - 1, gridPos.y + 1}) == nullptr) { openSpots.emplace_back(gridPos.x - 1, gridPos.y + 1); }
                if (gridPos.y < cellManager->grid->getHeight() - 1 && cellManager->grid->at({gridPos.x, gridPos.y + 1}) == nullptr) { openSpots.emplace_back(gridPos.x, gridPos.y + 1); }
                if (gridPos.x < cellManager->grid->getLength() - 1 && gridPos.y < cellManager->grid->getHeight() - 1 && cellManager->grid->at({gridPos.x + 1, gridPos.y + 1}) == nullptr) { openSpots.emplace_back(gridPos.x + 1, gridPos.y + 1); }

                if (openSpots.size() > 0)
                {
                    // last resort

                    // copy this cell to one of the open spots (grow)
        
                    int index = getRandomInt(openSpots.size() - 1);

                    cellManager->grid->createCell(cellManager->grid->at(gridPos)->getType(), openSpots[index]);

                    cellManager->grid->at(gridPos)->removeBehavior("grow");

                    return true;
                }
            }
        }
    }

    return false;
}