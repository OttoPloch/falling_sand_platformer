#include "heavy_behavior.hpp"

HeavyBehavior::HeavyBehavior() : Behavior("heavy", -1) {}

HeavyBehavior::HeavyBehavior(int weight) : Behavior("heavy", weight) {}

bool HeavyBehavior::update(Grid* grid, sf::Vector2u gridPos)
{
    if (gridPos.y < grid->getSize() - 1)
    {
        Cell* thisCell = grid->at(gridPos);
        int myWeight = thisCell->getOptionalSetting("heavy");

        Cell* bottomNeighbor = grid->at({gridPos.x, gridPos.y + 1});
        Cell* bottomLeftNeighbor = grid->at({gridPos.x - 1, gridPos.y + 1});
        Cell* bottomRightNeighbor = grid->at({gridPos.x + 1, gridPos.y + 1});
        Cell* leftNeighbor = grid->at({gridPos.x - 1, gridPos.y});
        Cell* rightNeighbor = grid->at({gridPos.x + 1, gridPos.y});


        // we know that the bottom neighbor
        // is not nullptr if this comes after
        // the falling behavior
        if (!bottomNeighbor->hasBehavior("static") && bottomNeighbor->getOptionalSetting("heavy") < myWeight)
        {
            // bottom

            grid->swap(gridPos, {gridPos.x, gridPos.y + 1});
        }
        else if (thisCell->hasBehavior("settle"))
        {
            // if this cell settles

            if (bottomLeftNeighbor != nullptr && bottomRightNeighbor != nullptr && !bottomLeftNeighbor->hasBehavior("static") && !bottomRightNeighbor->hasBehavior("static") && bottomLeftNeighbor->getOptionalSetting("heavy") < myWeight && bottomRightNeighbor->getOptionalSetting("heavy") < myWeight)
            {
                // if both bottom left and bottom right are valid

                if (getRandomInt(1) == 0)
                {
                    grid->swap(gridPos, {gridPos.x - 1, gridPos.y + 1});
                }
                else
                {
                    grid->swap(gridPos, {gridPos.x + 1, gridPos.y + 1});
                }

                return true;
            }
            else if (bottomLeftNeighbor != nullptr && !bottomLeftNeighbor->hasBehavior("static") && bottomLeftNeighbor->getOptionalSetting("heavy") < myWeight)
            {
                // bottom left

                grid->swap(gridPos, {gridPos.x - 1, gridPos.y + 1});

                return true;
            }
            else if (bottomRightNeighbor != nullptr && !bottomRightNeighbor->hasBehavior("static") && bottomRightNeighbor->getOptionalSetting("heavy") < myWeight)
            {
                // bottom right

                grid->swap(gridPos, {gridPos.x + 1, gridPos.y + 1});

                return true;
            }
        }
        else if (thisCell->hasBehavior("flow"))
        {
            // if this cell flows

            if (leftNeighbor != nullptr && rightNeighbor != nullptr && !leftNeighbor->hasBehavior("static") && !rightNeighbor->hasBehavior("static") && leftNeighbor->getOptionalSetting("heavy") < myWeight && rightNeighbor->getOptionalSetting("heavy") < myWeight)
            {
                // if both left and right are valid

                if (getRandomInt(1) == 0)
                {
                    grid->swap(gridPos, {gridPos.x - 1, gridPos.y});
                }
                else
                {
                    grid->swap(gridPos, {gridPos.x + 1, gridPos.y});
                }

                return true;
            }
            else if (leftNeighbor != nullptr && !leftNeighbor->hasBehavior("static") && leftNeighbor->getOptionalSetting("heavy") < myWeight)
            {
                // left

                grid->swap(gridPos, {gridPos.x - 1, gridPos.y});

                return true;
            }
            else if (rightNeighbor != nullptr && !rightNeighbor->hasBehavior("static") && rightNeighbor->getOptionalSetting("heavy") < myWeight)
            {
                // right

                grid->swap(gridPos, {gridPos.x + 1, gridPos.y});

                return true;
            }
        }
    }

    return false;
}