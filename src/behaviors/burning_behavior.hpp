#pragma once

#include "base/behavior.hpp"
#include "../game_classes/grid.hpp"
#include "../tools/get_random_number.hpp"
#include "../managers/cell_manager.hpp"

class BurningBehavior : public Behavior
{
public:
    BurningBehavior();

    BurningBehavior(int smokeChance);

    // overrides the parent class's update method
    bool update(CellManager* cellManager, sf::Vector2u gridPos) override;
};