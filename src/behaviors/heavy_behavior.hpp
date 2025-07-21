#pragma once

#include "base/behavior.hpp"
#include "../game_classes/grid.hpp"
#include "../game_classes/cell.hpp"

class HeavyBehavior : public Behavior
{
public:
    HeavyBehavior();

    HeavyBehavior(int weight);

    // overrides the parent class's update method
    bool update(Grid* grid, sf::Vector2u gridPos) override;
};