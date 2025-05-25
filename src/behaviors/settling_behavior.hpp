#pragma once

#include "../behavior.hpp"
#include "../grid.hpp"

class SettlingBehavior : public Behavior
{
public:
    SettlingBehavior();

    // overrides the parent class's update method
    bool update(Grid* grid, sf::Vector2u gridPos) override;
};