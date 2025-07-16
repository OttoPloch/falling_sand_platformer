#pragma once

#include "../behavior.hpp"
#include "../grid.hpp"
#include "../cell.hpp"

class RisingBehavior : public Behavior
{
public:
    RisingBehavior();

    RisingBehavior(int riseSpeed);

    // overrides the parent class's update method
    bool update(Grid* grid, sf::Vector2u gridPos) override;
};