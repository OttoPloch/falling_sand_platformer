#include "spreading_behavior.hpp"

SpreadingBehavior::SpreadingBehavior() : Behavior("spread", -1) {}

bool SpreadingBehavior::update(Grid* grid, sf::Vector2u gridPos)
{
    std::vector<sf::Vector2i> openSpots;

    if (grid->canMoveDistance(gridPos, {-1, -1})) { openSpots.push_back({-1, -1}); }
    if (grid->canMoveDistance(gridPos, {0, -1})) { openSpots.push_back({0, -1}); }
    if (grid->canMoveDistance(gridPos, {1, -1})) { openSpots.push_back({1, -1}); }
    if (grid->canMoveDistance(gridPos, {-1, 0})) { openSpots.push_back({-1, 0}); }
    if (grid->canMoveDistance(gridPos, {1, 0})) { openSpots.push_back({1, 0}); }
    if (grid->canMoveDistance(gridPos, {-1, 1})) { openSpots.push_back({-1, 1}); }
    if (grid->canMoveDistance(gridPos, {0, 1})) { openSpots.push_back({0, 1}); }
    if (grid->canMoveDistance(gridPos, {1, 1})) { openSpots.push_back({1, 1}); }

    if (openSpots.size() > 0)
    {
        grid->moveCell(gridPos, openSpots[getRandomInt(openSpots.size() - 1)]);

        return true;
    }

    return false;
}