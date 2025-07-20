#pragma once

#include "base/behavior.hpp"
#include "../grid.hpp"
#include "../cell.hpp"

class SettlingBehavior : public Behavior
{
public:
    SettlingBehavior();

    // overrides the parent class's update method
    bool update(Grid* grid, sf::Vector2u gridPos) override;
};