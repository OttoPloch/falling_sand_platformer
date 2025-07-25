#include "sink_behavior.hpp"

SinkBehavior::SinkBehavior() : Behavior("sink", -1) {}

bool SinkBehavior::update(CellManager* cellManager, sf::Vector2u gridPos)
{
    if ((cellManager->grid->at(gridPos)->getWeight() > 0 && gridPos.y < cellManager->grid->getSize() - 1) || (cellManager->grid->at(gridPos)->getWeight() < 0 && gridPos.y > 0))
    {
        // EVERYTHING HERE IS RELATIVE
        // 'bottom' here can refer to the cell above this one if the weight is below 0


        Cell* thisCell = cellManager->grid->at(gridPos);
        int myWeight = thisCell->getWeight();

        int sinkDirection;

        if (myWeight > 0)
        {
            sinkDirection = 1;
        }
        else if (myWeight < 0)
        {
            sinkDirection = -1;
        }
        else
        {
            std::cout << gridPos.x << ", " << gridPos.y << " of type " << cellManager->grid->at(gridPos)->getType() << " has the sink behavior but a weight of 0\n";
            assert(false);

            return false;
        }

        Cell* bottomNeighbor = cellManager->grid->at({gridPos.x, gridPos.y + sinkDirection});

        // we know that the bottom neighbor
        // is not nullptr if this comes after
        // the falling behavior
        //
        // ... you fool, if only you knew the hours
        // of time you would spend debugging to find
        // the reference to a nullptr. Never again (7/23/25)
        if (bottomNeighbor != nullptr && !bottomNeighbor->hasBehavior("static") && bottomNeighbor->getWeight() < myWeight)
        {
            // bottom

            cellManager->grid->swap(gridPos, {gridPos.x, gridPos.y + sinkDirection});
        }
        else if (thisCell->hasBehavior("settle"))
        {
            // if this cell settles

            Cell* bottomLeftNeighbor = cellManager->grid->at({gridPos.x - 1, gridPos.y + sinkDirection});
            Cell* bottomRightNeighbor = cellManager->grid->at({gridPos.x + 1, gridPos.y + sinkDirection});

            if (bottomLeftNeighbor != nullptr && bottomRightNeighbor != nullptr && !bottomLeftNeighbor->hasBehavior("static") && !bottomRightNeighbor->hasBehavior("static") && bottomLeftNeighbor->getWeight() < myWeight && bottomRightNeighbor->getWeight() < myWeight)
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
            else if (bottomLeftNeighbor != nullptr && !bottomLeftNeighbor->hasBehavior("static") && bottomLeftNeighbor->getWeight() < myWeight)
            {
                // bottom left

                cellManager->grid->swap(gridPos, {gridPos.x - 1, gridPos.y + sinkDirection});

                return true;
            }
            else if (bottomRightNeighbor != nullptr && !bottomRightNeighbor->hasBehavior("static") && bottomRightNeighbor->getWeight() < myWeight)
            {
                // bottom right

                cellManager->grid->swap(gridPos, {gridPos.x + 1, gridPos.y + sinkDirection});

                return true;
            }
        }
        else if (thisCell->hasBehavior("flow"))
        {
            // if this cell flows

            Cell* leftNeighbor = cellManager->grid->at({gridPos.x - 1, gridPos.y});
            Cell* rightNeighbor = cellManager->grid->at({gridPos.x + 1, gridPos.y});

            if (leftNeighbor != nullptr && rightNeighbor != nullptr && !leftNeighbor->hasBehavior("static") && !rightNeighbor->hasBehavior("static") && leftNeighbor->getWeight() < myWeight && rightNeighbor->getWeight() < myWeight)
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
            else if (leftNeighbor != nullptr && !leftNeighbor->hasBehavior("static") && leftNeighbor->getWeight() < myWeight)
            {
                // left

                cellManager->grid->swap(gridPos, {gridPos.x - 1, gridPos.y});

                return true;
            }
            else if (rightNeighbor != nullptr && !rightNeighbor->hasBehavior("static") && rightNeighbor->getWeight() < myWeight)
            {
                // right

                cellManager->grid->swap(gridPos, {gridPos.x + 1, gridPos.y});

                return true;
            }
        }
    }

    return false;
}