#include "falling_behavior.hpp"

#include "../game_classes/cell.hpp"
#include "../tools/collision.hpp"

FallingBehavior::FallingBehavior() : Behavior("fall", -1) {}

bool FallingBehavior::update(CellManager* cellManager, sf::Vector2u gridPos)
{
    Cell* cell = cellManager->grid->at(gridPos);

    if (cell->getWeight() != 0)
    {
        // increment the counter and get the weight value
        float weight = cell->incrementWeightCounter();

        // if the increment we did was enough to fall, check if we can move
        if (abs(cell->getWeightCounterInt()) >= 1)
        {
            // This doesnt take into account the cells current velocity.
            // It only does a basic check, and I'm not sure accessing velocity
            // when deciding to add more velocity is a good practice
            int maxYMove = maxMovableDistance(cellManager, gridPos, {0, cell->decrementWeightCounter()}, false).y;
    
            if (maxYMove != 0)
            {
                cellManager->grid->at(gridPos)->changeVelocity({0, maxYMove});

                return true;
            }
        }
        else
        {
            // didn't fall, but still incremented the counter
            return true;
        }
    }
    
    return false;
}