#include "planted_behavior.hpp"

PlantedBehavior::PlantedBehavior() : Behavior("planted", -1) {}

bool PlantedBehavior::update(CellManager* cellManager, sf::Vector2u gridPos)
{
    // this behavior is mostly for other cells to know about.
    // the only thing this behavior does on its own is check if it's still planted in soil
    // therefore, it is useful to put this behavior on other cells to have them kill the rest of the plant that was removed from soil

    // slows down the rate at which plants die
    if (cellManager->grid->at(gridPos)->getCellSettings()->getAge() < 1)
    {
        return true;
    }

    if (cellManager->grid->at({gridPos.x, gridPos.y + 1}) == nullptr || cellManager->grid->at({gridPos.x, gridPos.y + 1})->getType() != "soil")
    {
        if (cellManager->grid->at({gridPos.x - 1, gridPos.y + 1}) == nullptr || cellManager->grid->at({gridPos.x - 1, gridPos.y + 1})->getType() != "soil")
        {
            if (cellManager->grid->at({gridPos.x + 1, gridPos.y + 1}) == nullptr || cellManager->grid->at({gridPos.x + 1, gridPos.y + 1})->getType() != "soil")
            {
                // kill any plants attached to this one
                std::vector<Cell*> neighbors = cellManager->grid->at(gridPos)->getNeighbors();

                if (neighbors.size() > 0)
                {
                    for (int i = 0; i < neighbors.size(); i++)
                    {
                        // this neighbor is both the same type as this cell and has the same plantID
                        if (neighbors[i]->getCellSettings()->getPlantID() == cellManager->grid->at(gridPos)->getCellSettings()->getPlantID())
                        {
                            neighbors[i]->changeType("dead stem");

                            neighbors[i]->getCellSettings()->setPlantID(cellManager->grid->at(gridPos)->getCellSettings()->getPlantID());
                        }
                    }
                }

                // if there is no soil nearby, this cell is no longer planted
                cellManager->grid->at(gridPos)->changeType("dead stem");

                cellManager->grid->at(gridPos)->removeBehavior("planted");

                return true;
            }
        }
    }

    return false;
}