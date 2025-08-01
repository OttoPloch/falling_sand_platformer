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
#include "../behaviors/planted_behavior.hpp"
#include "../behaviors/seed_behavior.hpp"
#include "../behaviors/grow_behavior.hpp"
#include "../behaviors/splitting_behavior.hpp"
#include "../behaviors/burnable_behavior.hpp"

// Of note:
//     - To make a cell preset, follow the pattern below.
//
//          const CellPreset PRESETNAME(weight, canSmooth, color, { vector of behaviors as shared ptrs });
//
//     - Some behaviors, like CoolingBehavior or FlammableBehavior, have no real code in them and always return false.
//       These behaviors still can have settings tied to them or provide information to other behaviors.
//       For example, FlamingBehavior checks for cells around it with FlammableBehavior, and BurningBehavior checks
//       for cells around it with CoolingBehavior.
//     - FallingBehavior accounts for rising as well (if the cell has a negative weight)
//     - Sinkbehavior also accounts for negative weights
//     - If a cell is heavier than another cell, but does not have SinkBehavior, it will not sink
//     - The FlowingBehavior optionalSetting is the chance that the cell will flow if it can flow both ways, if it can only go one side it will
//     - Behaviors that use their optionalSetting as a chance use x/1000, where x is the optionalSetting (1 is least likely, 1000 is most, 0 is never or leave blank)
//     - canSmooth determines if the grid will use interpolation to smooth the movement of the cell, this can cause a delay if the cell is moving very rapidly, so
//       it is best to disable it for things like fire

const CellPreset SANDPRESET(1, true, sf::Color(252, 191, 98), {std::make_shared<FallingBehavior>(), std::make_shared<SinkBehavior>(), std::make_shared<SettlingBehavior>()});
const CellPreset WATERPRESET(0.5, true, sf::Color(19, 94, 186), {std::make_shared<FallingBehavior>(), std::make_shared<SinkBehavior>(), std::make_shared<FlowingBehavior>(1000), std::make_shared<CoolingBehavior>()});
const CellPreset FIREPRESET(0, false, sf::Color(255, 0, 0), {std::make_shared<BurningBehavior>(30), std::make_shared<FlamingBehavior>(), std::make_shared<SpreadingBehavior>()});
const CellPreset WOODPRESET(0, true, sf::Color(69, 44, 22), {std::make_shared<FlammableBehavior>(100), std::make_shared<StaticBehavior>()});
const CellPreset SMOKEPRESET(-1, true, sf::Color(55, 55, 55), {std::make_shared<FallingBehavior>(), std::make_shared<SinkBehavior>(), std::make_shared<SettlingBehavior>()});
const CellPreset SOILPRESET(0.25, true, sf::Color(110, 70, 30), {std::make_shared<FallingBehavior>(), std::make_shared<SettlingBehavior>()});
const CellPreset SEEDPRESET(0.3, true, sf::Color(15, 100, 30), {std::make_shared<FallingBehavior>(), std::make_shared<SeedBehavior>(3)});
const CellPreset STEMPRESET(0.3, true, sf::Color(25, 170, 35), {std::make_shared<SplittingBehavior>(100), std::make_shared<GrowBehavior>(0)});
const CellPreset DEADSTEMPRESET(0.2, true, sf::Color(80, 100, 30), {std::make_shared<PlantedBehavior>(), std::make_shared<FallingBehavior>(), std::make_shared<SettlingBehavior>(), std::make_shared<BurnableBehavior>(300)});
const CellPreset FLOWERPRESET(0, true, sf::Color(214, 55, 200), {std::make_shared<StaticBehavior>()});

const CellPreset TEMPPRESET(5, true, sf::Color(255, 255, 255), {std::make_shared<FallingBehavior>(), std::make_shared<SinkBehavior>()});

CellManager::CellManager() {}

CellManager::CellManager(float cellSize, sf::Vector2f cellOffset, Grid* grid, std::vector<std::shared_ptr<Being>>* beings, PlantManager* plantManager)
{
    presets = {
        {"sand", SANDPRESET},
        {"water", WATERPRESET},
        {"fire", FIREPRESET},
        {"wood", WOODPRESET},
        {"smoke", SMOKEPRESET},
        {"temp", TEMPPRESET},
        {"soil", SOILPRESET},
        {"seed", SEEDPRESET},
        {"stem", STEMPRESET},
        {"dead stem", DEADSTEMPRESET},
        {"flower", FLOWERPRESET}
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

    plantGrowUpChance = 600;

    this->plantManager = plantManager;
}