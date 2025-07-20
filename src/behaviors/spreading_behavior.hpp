#pragma once

#include "base/behavior.hpp"
#include "../grid.hpp"
#include "../tools/get_random_number.hpp"

class SpreadingBehavior : public Behavior
{
public:
    SpreadingBehavior();

    // overrides the parent class's update method
    bool update(Grid* grid, sf::Vector2u gridPos) override;
};