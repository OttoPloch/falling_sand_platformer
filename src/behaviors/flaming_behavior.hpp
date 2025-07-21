#pragma once

#include "base/behavior.hpp"
#include "../game_classes/grid.hpp"
#include "../tools/get_random_number.hpp"
#include "burning_behavior.hpp"

class FlamingBehavior : public Behavior
{
public:
    FlamingBehavior();

    // overrides the parent class's update method
    bool update(Grid* grid, sf::Vector2u gridPos) override;
};