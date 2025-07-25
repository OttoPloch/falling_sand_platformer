#pragma once

#include "base/behavior.hpp"
#include "../game_classes/grid.hpp"
#include "../game_classes/cell.hpp"
#include "../managers/cell_manager.hpp"

class SinkBehavior : public Behavior
{
public:
    SinkBehavior();

    // overrides the parent class's update method
    bool update(CellManager* cellManager, sf::Vector2u gridPos) override;
};