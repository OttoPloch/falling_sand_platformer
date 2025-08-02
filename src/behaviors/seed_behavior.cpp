#include "seed_behavior.hpp"

#include "../game_classes/cell.hpp"
#include "planted_behavior.hpp"

SeedBehavior::SeedBehavior() : Behavior("seed", -1) {}

SeedBehavior::SeedBehavior(int waterToSprout) : Behavior("seed", waterToSprout) {}

bool SeedBehavior::update(CellManager* cellManager, sf::Vector2u gridPos)
{
    Cell* thisCell = cellManager->grid->at(gridPos);

    // this cell is not planted
    if (!thisCell->hasBehavior("planted"))
    {
        // this cell can become planted only if it has soil directly beneath it
        if (cellManager->grid->at({gridPos.x, gridPos.y + 1}) != nullptr && cellManager->grid->at({gridPos.x, gridPos.y + 1})->getType() == "soil")
        {
            thisCell->addEndBehavior(std::make_shared<PlantedBehavior>());
        }
    }
    else
    {
        // this cell is planted

        // if any neighbors are water, absorb it and add to waterLevel
        std::vector<Cell*> neighbors = thisCell->getNeighbors();

        if (neighbors.size() > 0)
        {
            for (int i = 0; i < neighbors.size(); i++)
            {
                // if this neighbor is water, absorb it
                if (neighbors[i]->getType() == "water")
                {
                    cellManager->grid->removeCell(neighbors[i]->getPosition());

                    thisCell->getCellSettings()->addToWaterLevel(1);
                }

                // we have enough water to sprout
                if (thisCell->getCellSettings()->getWaterLevel() >= thisCell->getOptionalSetting("seed"))
                {
                    thisCell->changeType("stem");

                    thisCell->getCellSettings()->setPlantID(cellManager->grid->getNewPlantID());

                    thisCell->addEndBehavior(std::make_shared<PlantedBehavior>());

                    cellManager->plantManager->splitCounts[thisCell->getCellSettings()->getPlantID()] = 0;

                    return true;
                }
            }
        }
    }

    return false;
}