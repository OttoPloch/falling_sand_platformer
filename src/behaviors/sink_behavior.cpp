#include "sink_behavior.hpp"

#include "../tools/collision.hpp"
#include "../tools/get_points.hpp"

SinkBehavior::SinkBehavior() : Behavior("sink", -1) {}

bool SinkBehavior::update(CellManager* cellManager, sf::Vector2u gridPos)
{
    if ((cellManager->grid->at(gridPos)->getCellSettings()->getWeight() > 0.f && gridPos.y < cellManager->grid->getHeight() - 1) || (cellManager->grid->at(gridPos)->getCellSettings()->getWeight() < 0.f && gridPos.y > 0))
    {
        // EVERYTHING HERE IS RELATIVE
        // "bottom" here can refer to the cell above this one if the weight is below 0

        Cell* cell = cellManager->grid->at(gridPos);

        // no need to increment weight counter here, just checking if positive/negative
        float weight = cell->getCellSettings()->getWeight();

        int sinkDirection;

        if (weight > 0.f)
        {
            sinkDirection = 1;
        }
        else if (weight < 0.f)
        {
            sinkDirection = -1;
        }
        else
        {
            std::cout << gridPos.x << ", " << gridPos.y << " of type " << cellManager->grid->at(gridPos)->getType() << " has the sink behavior but a weight of 0\n";
            assert(false);

            return false;
        }

        // we know that the bottom neighbor
        // is not nullptr if this comes after
        // the falling behavior
        //
        // ... you fool, if only you knew the hours
        // of time you would spend debugging to find
        // the reference to a nullptr. Never again (7/23/25)
        if (cell->hasBehavior("fall"))
        {
            Cell* bottomNeighbor = cellManager->grid->at({gridPos.x, gridPos.y + sinkDirection});

            if (bottomNeighbor != nullptr && !bottomNeighbor->hasBehavior("static") && bottomNeighbor->getCellSettings()->getWeight() < weight)
            {
                if (!pointAllBeingsCollide(gridToWorldCoords(cellManager, sf::Vector2u(gridPos.x, gridPos.y + sinkDirection), true), cellManager->beings, cellManager->beingRectInflationSize))
                {
                    // bottom

                    cellManager->grid->swap(gridPos, {gridPos.x, gridPos.y + sinkDirection});
    
                    return true;
                }
            }
        }

        if (cell->hasBehavior("settle"))
        {
            // if this cell settles

            Cell* bottomLeftNeighbor = cellManager->grid->at({gridPos.x - 1, gridPos.y + sinkDirection});
            Cell* bottomRightNeighbor = cellManager->grid->at({gridPos.x + 1, gridPos.y + sinkDirection});

            if (bottomLeftNeighbor != nullptr && bottomRightNeighbor != nullptr && !bottomLeftNeighbor->hasBehavior("static") && !bottomRightNeighbor->hasBehavior("static") && bottomLeftNeighbor->getCellSettings()->getWeight() < weight && bottomRightNeighbor->getCellSettings()->getWeight() < weight)
            {
                if (!pointAllBeingsCollide(gridToWorldCoords(cellManager, sf::Vector2u(gridPos.x - 1, gridPos.y + sinkDirection), true), cellManager->beings, cellManager->beingRectInflationSize))
                {
                    if (!pointAllBeingsCollide(gridToWorldCoords(cellManager, sf::Vector2u(gridPos.x + 1, gridPos.y + sinkDirection), true), cellManager->beings, cellManager->beingRectInflationSize))
                    {
                        // if both bottom left and bottom right are valid
                        
                        if (getRandomInt(1) == 0)
                        {
                            cellManager->grid->swap(gridPos, {gridPos.x - 1, gridPos.y + sinkDirection});
                        }
                        else
                        {
                            cellManager->grid->swap(gridPos, {gridPos.x + 1, gridPos.y + sinkDirection});
                        }

                        return true;
                    }
                }
            }
            
            if (bottomLeftNeighbor != nullptr && !bottomLeftNeighbor->hasBehavior("static") && bottomLeftNeighbor->getCellSettings()->getWeight() < weight)
            {
                if (!pointAllBeingsCollide(gridToWorldCoords(cellManager, sf::Vector2u(gridPos.x - 1, gridPos.y + sinkDirection), true), cellManager->beings, cellManager->beingRectInflationSize))
                {
                    // bottom left
    
                    cellManager->grid->swap(gridPos, {gridPos.x - 1, gridPos.y + sinkDirection});
    
                    return true;
                }
            }
            
            if (bottomRightNeighbor != nullptr && !bottomRightNeighbor->hasBehavior("static") && bottomRightNeighbor->getCellSettings()->getWeight() < weight)
            {
                if (!pointAllBeingsCollide(gridToWorldCoords(cellManager, sf::Vector2u(gridPos.x + 1, gridPos.y + sinkDirection), true), cellManager->beings, cellManager->beingRectInflationSize))
                {
                    // bottom right
    
                    cellManager->grid->swap(gridPos, {gridPos.x + 1, gridPos.y + sinkDirection});
    
                    return true;
                }
            }
        }
        
        if (cell->hasBehavior("flow"))
        {
            // if this cell flows

            Cell* leftNeighbor = cellManager->grid->at({gridPos.x - 1, gridPos.y});
            Cell* rightNeighbor = cellManager->grid->at({gridPos.x + 1, gridPos.y});

            if (leftNeighbor != nullptr && rightNeighbor != nullptr && !leftNeighbor->hasBehavior("static") && !rightNeighbor->hasBehavior("static") && leftNeighbor->getCellSettings()->getWeight() < weight && rightNeighbor->getCellSettings()->getWeight() < weight)
            {
                if (!pointAllBeingsCollide(gridToWorldCoords(cellManager, sf::Vector2u(gridPos.x - 1, gridPos.y), true), cellManager->beings, cellManager->beingRectInflationSize))
                {
                    if (!pointAllBeingsCollide(gridToWorldCoords(cellManager, sf::Vector2u(gridPos.x + 1, gridPos.y), true), cellManager->beings, cellManager->beingRectInflationSize))
                    {
                        // if both left and right are valid
        
                        if (getRandomInt(1) == 0)
                        {
                            cellManager->grid->swap(gridPos, {gridPos.x - 1, gridPos.y});
                        }
                        else
                        {
                            cellManager->grid->swap(gridPos, {gridPos.x + 1, gridPos.y});
                        }
        
                        return true;
                    }
                }
            }
            else if (leftNeighbor != nullptr && !leftNeighbor->hasBehavior("static") && leftNeighbor->getCellSettings()->getWeight() < weight)
            {
                if (!pointAllBeingsCollide(gridToWorldCoords(cellManager, sf::Vector2u(gridPos.x - 1, gridPos.y), true), cellManager->beings, cellManager->beingRectInflationSize))
                {
                    // left
    
                    cellManager->grid->swap(gridPos, {gridPos.x - 1, gridPos.y});
    
                    return true;
                }
            }
            else if (rightNeighbor != nullptr && !rightNeighbor->hasBehavior("static") && rightNeighbor->getCellSettings()->getWeight() < weight)
            {
                if (!pointAllBeingsCollide(gridToWorldCoords(cellManager, sf::Vector2u(gridPos.x + 1, gridPos.y), true), cellManager->beings, cellManager->beingRectInflationSize))
                {
                    // right
    
                    cellManager->grid->swap(gridPos, {gridPos.x + 1, gridPos.y});
    
                    return true;
                }
            }
        }
    }

    return false;
}