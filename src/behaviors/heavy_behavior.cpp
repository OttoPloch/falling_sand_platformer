#include "heavy_behavior.hpp"

HeavyBehavior::HeavyBehavior() : Behavior("heavy") {}

bool HeavyBehavior::update(Grid* grid, sf::Vector2u gridPos)
{
    if (gridPos.y < grid->getSize() - 1)
    {
        // we know that the bottom neighbor
        // is not nullptr if this comes after
        // the falling behavior, same with the
        // bottom left and bottom right
        if (grid->at({gridPos.x, gridPos.y + 1})->getWeight() < grid->at(gridPos)->getWeight())
        {
            // bottom

            grid->swap(gridPos, {gridPos.x, gridPos.y + 1});
        }
        else if (grid->at(gridPos)->hasBehavior("settle"))
        {
            // if this cell settles

            if (grid->at({gridPos.x - 1, gridPos.y + 1}) != nullptr &&  grid->at({gridPos.x + 1, gridPos.y + 1}) != nullptr && grid->at({gridPos.x - 1, gridPos.y + 1})->getWeight() < grid->at(gridPos)->getWeight() && grid->at({gridPos.x + 1, gridPos.y + 1})->getWeight() < grid->at(gridPos)->getWeight())
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
            else if (grid->at({gridPos.x - 1, gridPos.y + 1}) != nullptr && grid->at({gridPos.x - 1, gridPos.y + 1})->getWeight() < grid->at(gridPos)->getWeight())
            {
                // bottom left

                grid->swap(gridPos, {gridPos.x - 1, gridPos.y + 1});

                return true;
            }
            else if (grid->at({gridPos.x + 1, gridPos.y + 1}) != nullptr && grid->at({gridPos.x + 1, gridPos.y + 1})->getWeight() < grid->at(gridPos)->getWeight())
            {
                // bottom right

                grid->swap(gridPos, {gridPos.x + 1, gridPos.y + 1});

                return true;
            }
        }
        else if (grid->at(gridPos)->hasBehavior("flow"))
        {
            // if this cell flows

            if (grid->at({gridPos.x - 1, gridPos.y}) != nullptr && grid->at({gridPos.x + 1, gridPos.y}) != nullptr && grid->at({gridPos.x - 1, gridPos.y})->getWeight() < grid->at(gridPos)->getWeight() && grid->at({gridPos.x + 1, gridPos.y})->getWeight() < grid->at(gridPos)->getWeight())
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
            else if (grid->at({gridPos.x - 1, gridPos.y}) != nullptr && grid->at({gridPos.x - 1, gridPos.y})->getWeight() < grid->at(gridPos)->getWeight())
            {
                // left

                grid->swap(gridPos, {gridPos.x - 1, gridPos.y});

                return true;
            }
            else if (grid->at({gridPos.x + 1, gridPos.y}) != nullptr && grid->at({gridPos.x + 1, gridPos.y})->getWeight() < grid->at(gridPos)->getWeight())
            {
                // right

                grid->swap(gridPos, {gridPos.x + 1, gridPos.y});

                return true;
            }
        }
    }

    return false;
}