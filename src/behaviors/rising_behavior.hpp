#pragma once

#include "base/behavior.hpp"
#include "../game_classes/grid.hpp"
#include "../game_classes/cell.hpp"

class RisingBehavior : public Behavior
{
public:
    RisingBehavior();

    RisingBehavior(int riseSpeed);

    // overrides the parent class's update method
    bool update(Grid* grid, sf::Vector2u gridPos) override;
};