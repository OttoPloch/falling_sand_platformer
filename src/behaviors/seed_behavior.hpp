#pragma once

#include "base/behavior.hpp"
#include "../game_classes/grid.hpp"
#include "../managers/cell_manager.hpp"

class SeedBehavior : public Behavior
{
public:
    SeedBehavior();

    SeedBehavior(int waterToSprout);

    // overrides the parent class's update method
    bool update(CellManager* cellManager, sf::Vector2u gridPos) override;
};