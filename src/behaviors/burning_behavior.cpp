#include "burning_behavior.hpp"

#include "../cell.hpp"

BurningBehavior::BurningBehavior() : Behavior("burning", -1) {}

BurningBehavior::BurningBehavior(int smokeChance) : Behavior("burning", smokeChance) {}

bool BurningBehavior::update(Grid* grid, sf::Vector2u gridPos)
{
    std::vector<sf::Vector2i> Neighbors;

    if (gridPos.x > 0 && gridPos.y > 0 && grid->at({gridPos.x - 1, gridPos.y - 1}) != nullptr && grid->at({gridPos.x - 1, gridPos.y - 1})->hasBehavior("cooling")) { grid->removeCell(gridPos); return true; }
    if (gridPos.y > 0 && grid->at({gridPos.x, gridPos.y - 1}) != nullptr && grid->at({gridPos.x, gridPos.y - 1})->hasBehavior("cooling")) { grid->removeCell(gridPos); return true; }
    if (gridPos.x < grid->getSizeOfRow(gridPos.y) - 1 && gridPos.y > 0 && grid->at({gridPos.x + 1, gridPos.y - 1}) != nullptr && grid->at({gridPos.x + 1, gridPos.y - 1})->hasBehavior("cooling")) { grid->removeCell(gridPos); return true; }
    if (gridPos.x > 0 && grid->at({gridPos.x - 1, gridPos.y}) != nullptr && grid->at({gridPos.x - 1, gridPos.y})->hasBehavior("cooling")) { grid->removeCell(gridPos); }
    if (gridPos.x < grid->getSizeOfRow(gridPos.y) - 1 && grid->at({gridPos.x + 1, gridPos.y}) != nullptr && grid->at({gridPos.x + 1, gridPos.y})->hasBehavior("cooling")) { grid->removeCell(gridPos); return true; }
    if (gridPos.x > 0 && gridPos.y < grid->getSize() - 1 && grid->at({gridPos.x - 1, gridPos.y + 1}) != nullptr && grid->at({gridPos.x - 1, gridPos.y + 1})->hasBehavior("cooling")) { grid->removeCell(gridPos); return true; }
    if (gridPos.y < grid->getSize() - 1 && grid->at({gridPos.x, gridPos.y + 1}) != nullptr && grid->at({gridPos.x, gridPos.y + 1})->hasBehavior("cooling")) { grid->removeCell(gridPos); return true; }
    if (gridPos.x < grid->getSizeOfRow(gridPos.y) - 1 && gridPos.y < grid->getSize() - 1 && grid->at({gridPos.x + 1, gridPos.y + 1}) != nullptr && grid->at({gridPos.x + 1, gridPos.y + 1})->hasBehavior("cooling")) { grid->removeCell(gridPos); return true; }
    
    if (getRandomInt(999) + 1 <= grid->at(gridPos)->getOptionalSetting("burning"))
    {
        grid->at(gridPos)->changeType("smoke");

        return true;
    }

    return false;
}