#pragma once

#include "../behavior.hpp"
#include "../grid.hpp"

class FlammableBehavior : public Behavior
{
public:
    FlammableBehavior();

    FlammableBehavior(int flammability);

    // overrides the parent class's update method
    bool update(Grid* grid, sf::Vector2u gridPos) override;
};