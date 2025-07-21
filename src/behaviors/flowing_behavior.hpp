#pragma once

#include "base/behavior.hpp"
#include "../game_classes/grid.hpp"

class FlowingBehavior : public Behavior
{
public:
    FlowingBehavior();

    // overrides the parent class's update method
    bool update(Grid* grid, sf::Vector2u gridPos) override;
};