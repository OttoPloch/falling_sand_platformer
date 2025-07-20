#pragma once

#include "base/behavior.hpp"
#include "../grid.hpp"

class StaticBehavior : public Behavior
{
public:
    StaticBehavior();

    // overrides the parent class's update method
    bool update(Grid* grid, sf::Vector2u gridPos) override;
};