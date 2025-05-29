#include "spreading_behavior.hpp"

FlamingBehavior::FlamingBehavior() : Behavior("spread", -1) {}

bool FlamingBehavior::update(Grid* grid, sf::Vector2u gridPos)
{
    std::vector<sf::Vector2i> openSpots;

    if (gridPos.x > 0 && gridPos.y > 0 && grid->at({gridPos.x - 1, gridPos.y - 1}) == nullptr) { openSpots.push_back({-1, -1}); }
    if (gridPos.y > 0 && grid->at({gridPos.x, gridPos.y - 1}) == nullptr) { openSpots.push_back({0, -1}); }
    if (gridPos.x < grid->getSizeOfRow(gridPos.y) - 1 && gridPos.y > 0 && grid->at({gridPos.x + 1, gridPos.y - 1}) == nullptr) { openSpots.push_back({1, -1}); }
    if (gridPos.x > 0 && grid->at({gridPos.x - 1, gridPos.y}) == nullptr) { openSpots.push_back({-1, 0}); }
    if (gridPos.x < grid->getSizeOfRow(gridPos.y) - 1 && grid->at({gridPos.x + 1, gridPos.y}) == nullptr) { openSpots.push_back({1, 0}); }
    if (gridPos.x > 0 && gridPos.y < grid->getSize() - 1 && grid->at({gridPos.x - 1, gridPos.y + 1}) == nullptr) { openSpots.push_back({-1, 1}); }
    if (gridPos.y < grid->getSize() - 1 && grid->at({gridPos.x, gridPos.y + 1}) == nullptr) { openSpots.push_back({0, 1}); }
    if (gridPos.x < grid->getSizeOfRow(gridPos.y) - 1 && gridPos.y < grid->getSize() - 1 && grid->at({gridPos.x + 1, gridPos.y + 1}) == nullptr) { openSpots.push_back({1, 1}); }

    if (openSpots.size() > 0)
    {
        grid->moveCell(gridPos, openSpots[getRandomInt(openSpots.size() - 1)]);

        return true;
    }

    return false;
}