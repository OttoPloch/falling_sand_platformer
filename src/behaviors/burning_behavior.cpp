#include "burning_behavior.hpp"

#include "../game_classes/cell.hpp"

BurningBehavior::BurningBehavior() : Behavior("burning", -1) {}

BurningBehavior::BurningBehavior(int smokeChance) : Behavior("burning", smokeChance) {}

bool BurningBehavior::update(CellManager* cellManager, sf::Vector2u gridPos)
{
    if (gridPos.x > 0 && gridPos.y > 0 && cellManager->grid->at({gridPos.x - 1, gridPos.y - 1}) != nullptr && cellManager->grid->at({gridPos.x - 1, gridPos.y - 1})->hasBehavior("cooling")) { cellManager->grid->removeCell(gridPos); return true; }
    if (gridPos.y > 0 && cellManager->grid->at({gridPos.x, gridPos.y - 1}) != nullptr && cellManager->grid->at({gridPos.x, gridPos.y - 1})->hasBehavior("cooling")) { cellManager->grid->removeCell(gridPos); return true; }
    if (gridPos.x < cellManager->grid->getSizeOfRow(gridPos.y) - 1 && gridPos.y > 0 && cellManager->grid->at({gridPos.x + 1, gridPos.y - 1}) != nullptr && cellManager->grid->at({gridPos.x + 1, gridPos.y - 1})->hasBehavior("cooling")) { cellManager->grid->removeCell(gridPos); return true; }
    if (gridPos.x > 0 && cellManager->grid->at({gridPos.x - 1, gridPos.y}) != nullptr && cellManager->grid->at({gridPos.x - 1, gridPos.y})->hasBehavior("cooling")) { cellManager->grid->removeCell(gridPos); return true; }
    if (gridPos.x < cellManager->grid->getSizeOfRow(gridPos.y) - 1 && cellManager->grid->at({gridPos.x + 1, gridPos.y}) != nullptr && cellManager->grid->at({gridPos.x + 1, gridPos.y})->hasBehavior("cooling")) { cellManager->grid->removeCell(gridPos); return true; }
    if (gridPos.x > 0 && gridPos.y < cellManager->grid->getSize() - 1 && cellManager->grid->at({gridPos.x - 1, gridPos.y + 1}) != nullptr && cellManager->grid->at({gridPos.x - 1, gridPos.y + 1})->hasBehavior("cooling")) { cellManager->grid->removeCell(gridPos); return true; }
    if (gridPos.y < cellManager->grid->getSize() - 1 && cellManager->grid->at({gridPos.x, gridPos.y + 1}) != nullptr && cellManager->grid->at({gridPos.x, gridPos.y + 1})->hasBehavior("cooling")) { cellManager->grid->removeCell(gridPos); return true; }
    if (gridPos.x < cellManager->grid->getSizeOfRow(gridPos.y) - 1 && gridPos.y < cellManager->grid->getSize() - 1 && cellManager->grid->at({gridPos.x + 1, gridPos.y + 1}) != nullptr && cellManager->grid->at({gridPos.x + 1, gridPos.y + 1})->hasBehavior("cooling")) { cellManager->grid->removeCell(gridPos); return true; }
    
    if (getRandomInt(999) + 1 <= cellManager->grid->at(gridPos)->getOptionalSetting("burning"))
    {
        cellManager->grid->at(gridPos)->changeType("smoke");

        return true;
    }

    return false;
}