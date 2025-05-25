#pragma once

#include "../behavior.hpp"
#include "../grid.hpp"

class FallingBehavior : public Behavior
{
public:
    FallingBehavior();

    // overrides the parent class's update method
    bool update(Grid* grid, sf::Vector2u gridPos) override;
};