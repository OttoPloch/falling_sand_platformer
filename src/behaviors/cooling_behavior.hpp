#pragma once

#include "../behavior.hpp"
#include "../grid.hpp"

class CoolingBehavior : public Behavior
{
public:
    CoolingBehavior();

    // overrides the parent class's update method
    bool update(Grid* grid, sf::Vector2u gridPos) override;
};