#pragma once

#include "../behavior.hpp"
#include "../grid.hpp"
#include "../get_random_number.hpp"

class BurningBehavior : public Behavior
{
public:
    BurningBehavior();

    // overrides the parent class's update method
    bool update(Grid* grid, sf::Vector2u gridPos) override;
};