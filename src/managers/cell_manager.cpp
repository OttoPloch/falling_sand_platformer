#include "cell_manager.hpp"

#include "../behaviors/falling_behavior.hpp"
#include "../behaviors/settling_behavior.hpp"
#include "../behaviors/flowing_behavior.hpp"
#include "../behaviors/sink_behavior.hpp"
#include "../behaviors/spreading_behavior.hpp"
#include "../behaviors/flaming_behavior.hpp"
#include "../behaviors/flammable_behavior.hpp"
#include "../behaviors/static_behavior.hpp"
#include "../behaviors/burning_behavior.hpp"
#include "../behaviors/cooling_behavior.hpp"

// Of note:
//     - To make a cell preset, follow the pattern below.
//
//          const CellPreset PRESETNAME(weight, color, { vector of behaviors as shared ptrs });
//
//     - FallingBehavior accounts for rising as well (if the cell has a negative weight)
//     - Sinkbehavior also accounts for negative weights
//     - If a cell is heavier than another cell, but does not have SinkBehavior, it will not sink

const CellPreset SANDPRESET(3, sf::Color(252, 191, 98), {std::make_shared<FallingBehavior>(), std::make_shared<SinkBehavior>(), std::make_shared<SettlingBehavior>()});
const CellPreset WATERPRESET(2, sf::Color(19, 94, 186), {std::make_shared<FallingBehavior>(), std::make_shared<SinkBehavior>(), std::make_shared<FlowingBehavior>(), std::make_shared<CoolingBehavior>()});
const CellPreset FIREPRESET(0, sf::Color(255, 0, 0), {std::make_shared<BurningBehavior>(30), std::make_shared<FlamingBehavior>(), std::make_shared<SpreadingBehavior>()});
const CellPreset WOODPRESET(0, sf::Color(99, 64, 28), {std::make_shared<FlammableBehavior>(100), std::make_shared<StaticBehavior>()});
const CellPreset SMOKEPRESET(-1, sf::Color(55, 55, 55), {std::make_shared<FallingBehavior>(), std::make_shared<SinkBehavior>(), std::make_shared<SettlingBehavior>()});

const CellPreset TEMPPRESET(5, sf::Color(255, 255, 255), {std::make_shared<FallingBehavior>(), std::make_shared<SinkBehavior>()});

CellManager::CellManager() {}

CellManager::CellManager(float cellSize, sf::Vector2f cellOffset, Grid* grid, std::vector<std::shared_ptr<Being>>* beings)
{
    presets = {
        {"sand", SANDPRESET},
        {"water", WATERPRESET},
        {"fire", FIREPRESET},
        {"wood", WOODPRESET},
        {"smoke", SMOKEPRESET},
        {"temp", TEMPPRESET}
    };

    this->grid = grid;

    this->beings = beings;
    
    this->cellSize = cellSize;
    
    this->cellOffset = cellOffset;

    // This is about what the max effective size of the being could be
    // given the same coded size if I implemented drawing beings in squares aligned
    // to the grid. This is because any bigger size would cause some edge pieces to
    // be partially black when the being is rotated. So, we can only use a section of
    // the texture if it can take up a full cell of space. Holy yap fest.
    //beingRectInflationSize = {-cellSize, -cellSize};

    // The - 1 is so that a flat surface will not have an extra layer of collision
    beingRectInflationSize = {cellSize - 1, cellSize - 1};
}