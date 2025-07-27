#pragma once

#include "base/behavior.hpp"
#include "../game_classes/grid.hpp"
#include "../managers/cell_manager.hpp"

class FlowingBehavior : public Behavior
{
public:
    FlowingBehavior();

    FlowingBehavior(int flowChance);

    // overrides the parent class's update method
    bool update(CellManager* cellManager, sf::Vector2u gridPos) override;
};