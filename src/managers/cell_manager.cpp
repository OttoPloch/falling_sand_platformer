#include "cell_manager.hpp"

const CellPreset SANDPRESET(sf::Color(252, 191, 98), {std::make_shared<FallingBehavior>(), std::make_shared<HeavyBehavior>(3), std::make_shared<SettlingBehavior>()});
const CellPreset WATERPRESET(sf::Color(19, 94, 186), {std::make_shared<FallingBehavior>(), std::make_shared<HeavyBehavior>(2), std::make_shared<FlowingBehavior>(), std::make_shared<CoolingBehavior>()});
const CellPreset FIREPRESET(sf::Color(255, 0, 0), {std::make_shared<BurningBehavior>(500), std::make_shared<FlamingBehavior>(), std::make_shared<SpreadingBehavior>()});
const CellPreset WOODPRESET(sf::Color(99, 64, 28), {std::make_shared<FlammableBehavior>(100), std::make_shared<StaticBehavior>()});
const CellPreset SMOKEPRESET(sf::Color(55, 55, 55), {std::make_shared<RisingBehavior>(1), std::make_shared<SettlingBehavior>()});

CellManager::CellManager()
{
    presets = {
        {"sand", SANDPRESET},
        {"water", WATERPRESET},
        {"fire", FIREPRESET},
        {"wood", WOODPRESET},
        {"smoke", SMOKEPRESET}
    };
}