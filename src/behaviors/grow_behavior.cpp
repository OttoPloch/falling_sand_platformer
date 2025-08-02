#include "grow_behavior.hpp"

#include "../game_classes/cell.hpp"

GrowBehavior::GrowBehavior() : Behavior("grow", -1) {}

GrowBehavior::GrowBehavior(int chanceToEnd) : Behavior("grow", chanceToEnd) {}

bool GrowBehavior::update(CellManager* cellManager, sf::Vector2u gridPos)
{
    Grid* grid = cellManager->grid;
    Cell* thisCell = grid->at(gridPos);

    // slows down the rate at which plants grow
    if (grid->at(gridPos)->getCellSettings()->getAge() < 1)
    {
        return false;
    }

    std::vector<sf::Vector2u> openSpots;
    
    // most preferred spots
    if (gridPos.x > 0 && grid->at({gridPos.x - 1, gridPos.y}) == nullptr) { openSpots.emplace_back(gridPos.x - 1, gridPos.y); }
    if (gridPos.x < grid->getLength() - 1 && grid->at({gridPos.x + 1, gridPos.y}) == nullptr) { openSpots.emplace_back(gridPos.x + 1, gridPos.y); }
    
    if (openSpots.size() == 0)
    {
        // next preffered
        if (gridPos.x > 0 && gridPos.y > 0 && grid->at({gridPos.x - 1, gridPos.y - 1}) == nullptr) { openSpots.emplace_back(gridPos.x - 1, gridPos.y - 1); }
        if (gridPos.x < grid->getLength() - 1 && gridPos.y > 0 && grid->at({gridPos.x + 1, gridPos.y - 1}) == nullptr) { openSpots.emplace_back(gridPos.x + 1, gridPos.y - 1); }
    }

    sf::Vector2u posToCreateAt;

    if (openSpots.size() > 0)
    {
        if (gridPos.y > 0 && grid->at({gridPos.x, gridPos.y - 1}) == nullptr)
        {
            // can go up and can go somehwere else, pick randomly
            if (getRandomInt(999) + 1 <= cellManager->plantGrowUpChance)
            {
                posToCreateAt = {gridPos.x, gridPos.y - 1};
            }
            else
            {
                posToCreateAt = openSpots[getRandomInt(openSpots.size() - 1)];
            }
        }
        else
        {
            // can't go up but can go somewhere else
            posToCreateAt = openSpots[getRandomInt(openSpots.size() - 1)];
        }
    }
    else if (gridPos.y > 0 && grid->at({gridPos.x, gridPos.y - 1}) == nullptr)
    {
        // can only go up
        posToCreateAt = {gridPos.x, gridPos.y - 1};
    }
    else
    {
        thisCell->removeBehavior("grow");
        thisCell->removeBehavior("split");

        return false;
    }

    // chance to stop growing and make a flower
    if (getRandomInt(999) + 1 <= thisCell->getOptionalSetting("grow") || cellManager->plantManager->splitCounts[thisCell->getCellSettings()->getPlantID()] >= cellManager->plantManager->maxPlantSplits)
    {
        thisCell->changeType("flower");

        bool onLeft = (gridPos.x == 0);
        bool onRight = (gridPos.x == grid->getLength() - 1);
        bool onTop = (gridPos.y == 0);
        bool onBottom = (gridPos.y == grid->getHeight() - 1);

        // jumpscare

        if (!onLeft && !onTop)
        {
            if (grid->at({gridPos.x - 1, gridPos.y - 1}) == nullptr) { grid->createCell("flower", {gridPos.x - 1, gridPos.y - 1}, thisCell->getCellSettings()->getPlantID()); }
            else if (grid->at({gridPos.x - 1, gridPos.y - 1})->getCellSettings()->getPlantID() == thisCell->getCellSettings()->getPlantID()) { grid->at({gridPos.x - 1, gridPos.y - 1})->changeType("flower"); }
        }
        if (!onTop)
        {
            if (grid->at({gridPos.x, gridPos.y - 1}) == nullptr) { grid->createCell("flower", {gridPos.x, gridPos.y - 1}, thisCell->getCellSettings()->getPlantID()); }
            else if (grid->at({gridPos.x, gridPos.y - 1})->getCellSettings()->getPlantID() == thisCell->getCellSettings()->getPlantID()) { grid->at({gridPos.x, gridPos.y - 1})->changeType("flower"); }
        }
        if (!onLeft)
        {
            if (grid->at({gridPos.x - 1, gridPos.y}) == nullptr) { grid->createCell("flower", {gridPos.x - 1, gridPos.y}, thisCell->getCellSettings()->getPlantID()); }
            else if (grid->at({gridPos.x - 1, gridPos.y})->getCellSettings()->getPlantID() == thisCell->getCellSettings()->getPlantID()) { grid->at({gridPos.x - 1, gridPos.y})->changeType("flower"); }
        }

        return true;
    }

    // create a new cell with the same type as this one at one of the positions in openSpots, with this cell's plantID.
    grid->createCell(thisCell->getType(), posToCreateAt, thisCell->getCellSettings()->getPlantID());

    thisCell->removeBehavior("grow");
    thisCell->removeBehavior("split");

    return true;
}