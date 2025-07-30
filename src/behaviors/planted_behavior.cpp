#include "planted_behavior.hpp"

PlantedBehavior::PlantedBehavior() : Behavior("planted", -1) {}

bool PlantedBehavior::update(CellManager* cellManager, sf::Vector2u gridPos)
{
    if (cellManager->grid->at({gridPos.x, gridPos.y + 1}) == nullptr || cellManager->grid->at({gridPos.x, gridPos.y + 1})->getType() != "soil")
    {
        if (cellManager->grid->at({gridPos.x - 1, gridPos.y + 1}) == nullptr || cellManager->grid->at({gridPos.x - 1, gridPos.y + 1})->getType() != "soil")
        {
            if (cellManager->grid->at({gridPos.x + 1, gridPos.y + 1}) == nullptr || cellManager->grid->at({gridPos.x + 1, gridPos.y + 1})->getType() != "soil")
            {
                // kill any plants attached to this one
                if (gridPos.x > 0 && gridPos.y > 0 && cellManager->grid->at({gridPos.x - 1, gridPos.y - 1}) != nullptr && cellManager->grid->at({gridPos.x - 1, gridPos.y - 1})->getType() == cellManager->grid->at(gridPos)->getType()) { cellManager->grid->at({gridPos.x - 1, gridPos.y - 1})->changeType("dead stem"); }
                if (gridPos.y > 0 && cellManager->grid->at({gridPos.x, gridPos.y - 1}) != nullptr && cellManager->grid->at({gridPos.x, gridPos.y - 1})->getType() == cellManager->grid->at(gridPos)->getType()) { cellManager->grid->at({gridPos.x, gridPos.y - 1})->changeType("dead stem"); }
                if (gridPos.x < cellManager->grid->getLength() - 1 && gridPos.y > 0 && cellManager->grid->at({gridPos.x + 1, gridPos.y - 1}) != nullptr && cellManager->grid->at({gridPos.x + 1, gridPos.y - 1})->getType() == cellManager->grid->at(gridPos)->getType()) { cellManager->grid->at({gridPos.x + 1, gridPos.y - 1})->changeType("dead stem"); }
                if (gridPos.x > 0 && cellManager->grid->at({gridPos.x - 1, gridPos.y}) != nullptr && cellManager->grid->at({gridPos.x - 1, gridPos.y})->getType() == cellManager->grid->at(gridPos)->getType()) { cellManager->grid->at({gridPos.x - 1, gridPos.y})->changeType("dead stem"); }
                if (gridPos.x < cellManager->grid->getLength() - 1 && cellManager->grid->at({gridPos.x + 1, gridPos.y}) != nullptr && cellManager->grid->at({gridPos.x + 1, gridPos.y})->getType() == cellManager->grid->at(gridPos)->getType()) { cellManager->grid->at({gridPos.x + 1, gridPos.y})->changeType("dead stem"); }
                if (gridPos.x > 0 && gridPos.y < cellManager->grid->getHeight() - 1 && cellManager->grid->at({gridPos.x - 1, gridPos.y + 1}) != nullptr && cellManager->grid->at({gridPos.x - 1, gridPos.y + 1})->getType() == cellManager->grid->at(gridPos)->getType()) { cellManager->grid->at({gridPos.x - 1, gridPos.y + 1})->changeType("dead stem"); }
                if (gridPos.y < cellManager->grid->getHeight() - 1 && cellManager->grid->at({gridPos.x, gridPos.y + 1}) != nullptr && cellManager->grid->at({gridPos.x, gridPos.y + 1})->getType() == cellManager->grid->at(gridPos)->getType()) { cellManager->grid->at(gridPos)->changeType("dead stem"); }
                if (gridPos.x < cellManager->grid->getLength() - 1 && gridPos.y < cellManager->grid->getHeight() - 1 && cellManager->grid->at({gridPos.x + 1, gridPos.y + 1}) != nullptr && cellManager->grid->at({gridPos.x + 1, gridPos.y + 1})->getType() == cellManager->grid->at(gridPos)->getType()) { cellManager->grid->at({gridPos.x + 1, gridPos.y + 1})->changeType("dead stem"); }

                // if there is no soil nearby, this cell is no longer planted
                cellManager->grid->at(gridPos)->changeType("dead stem");

                return true;
            }
        }
    }

    return false;
}