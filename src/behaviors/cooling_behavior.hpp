#pragma once

#include "base/behavior.hpp"
#include "../game_classes/grid.hpp"

class CoolingBehavior : public Behavior
{
public:
    CoolingBehavior();

    // overrides the parent class's update method
    bool update(Grid* grid, sf::Vector2u gridPos) override;
};