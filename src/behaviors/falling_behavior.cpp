#include "falling_behavior.hpp"

#include "../game_classes/cell.hpp"
#include "../tools/collision.hpp"

FallingBehavior::FallingBehavior() : Behavior("fall", -1) {}

bool FallingBehavior::update(CellManager* cellManager, sf::Vector2u gridPos)
{
    int weight = cellManager->grid->at(gridPos)->getWeight();

    if (weight != 0)
    {
        // This doesnt take into account the cells current velocity.
        // It only does a basic check, and I'm not sure accessing velocity
        // when deciding to add more velocity is a good practice
        int maxYMove = maxMovableDistance(cellManager, gridPos, {0, weight}).y;

        if (maxYMove != 0)
        {
            cellManager->grid->at(gridPos)->changeVelocity({0, maxYMove});

            return true;
        }
    }
    
    return false;
}