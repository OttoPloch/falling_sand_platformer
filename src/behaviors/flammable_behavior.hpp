#pragma once

#include "base/behavior.hpp"
#include "../game_classes/grid.hpp"

class FlammableBehavior : public Behavior
{
public:
    FlammableBehavior();

    FlammableBehavior(int flammability);

    // overrides the parent class's update method
    bool update(Grid* grid, sf::Vector2u gridPos) override;
};