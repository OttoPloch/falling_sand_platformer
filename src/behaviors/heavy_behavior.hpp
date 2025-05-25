#pragma once

#include "../behavior.hpp"
#include "../grid.hpp"
#include "../cell.hpp"

class HeavyBehavior : public Behavior
{
public:
    HeavyBehavior();

    // overrides the parent class's update method
    bool update(Grid* grid, sf::Vector2u gridPos) override;
};