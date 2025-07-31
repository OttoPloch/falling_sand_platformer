#include "splitting_behavior.hpp"

#include "../game_classes/cell.hpp"

SplittingBehavior::SplittingBehavior() : Behavior("split", -1) {}

SplittingBehavior::SplittingBehavior(int chanceToSplit) : Behavior("split", chanceToSplit) {}

bool SplittingBehavior::update(CellManager* cellManager, sf::Vector2u gridPos)
{
    Cell* thisCell = cellManager->grid->at(gridPos);
    
    if (getRandomInt(999) + 1 <= thisCell->getOptionalSetting("split"))
    {
        std::vector<sf::Vector2u> openSpots;
        
        // most preferred spots
        if (gridPos.x > 0 && cellManager->grid->at({gridPos.x - 1, gridPos.y}) == nullptr) { openSpots.emplace_back(gridPos.x - 1, gridPos.y); }
        if (gridPos.x < cellManager->grid->getLength() - 1 && cellManager->grid->at({gridPos.x + 1, gridPos.y}) == nullptr) { openSpots.emplace_back(gridPos.x + 1, gridPos.y); }
        
        // unlike GrowBehavior, moving straight up is part of the positions to put in openSpots, since we just want to split and have no bias where to go
        if (gridPos.y > 0 && cellManager->grid->at({gridPos.x, gridPos.y - 1}) == nullptr) { openSpots.emplace_back(gridPos.x, gridPos.y - 1); }
        
        if (openSpots.size() == 0)
        {
            // next preffered
            if (gridPos.x > 0 && gridPos.y > 0 && cellManager->grid->at({gridPos.x - 1, gridPos.y - 1}) == nullptr) { openSpots.emplace_back(gridPos.x - 1, gridPos.y - 1); }
            if (gridPos.x < cellManager->grid->getLength() - 1 && gridPos.y > 0 && cellManager->grid->at({gridPos.x + 1, gridPos.y - 1}) == nullptr) { openSpots.emplace_back(gridPos.x + 1, gridPos.y - 1); }
        }

        sf::Vector2u pos1, pos2;

        if (openSpots.size() > 1)
        {
            int index1, index2;

            index1 = getRandomInt(openSpots.size() - 1);

            // very bad? probably
            do {
                index2 = getRandomInt(openSpots.size() - 1);
            } while (index2 == index1);
            
            cellManager->grid->createCell(thisCell->getType(), openSpots[index1], thisCell->getCellSettings()->getPlantID());
            cellManager->grid->createCell(thisCell->getType(), openSpots[index2], thisCell->getCellSettings()->getPlantID());

            thisCell->removeBehavior("grow");
        }
        else
        {
            thisCell->removeBehavior("split");
        }
    }
    
    return false;
}