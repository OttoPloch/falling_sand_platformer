#pragma once

#include "base/behavior.hpp"
#include "../grid.hpp"
#include "../cell.hpp"

class HeavyBehavior : public Behavior
{
public:
    HeavyBehavior();

    HeavyBehavior(int weight);

    // overrides the parent class's update method
    bool update(Grid* grid, sf::Vector2u gridPos) override;
};