#include "cell_manager.hpp"

#include "../behaviors/falling_behavior.hpp"
#include "../behaviors/settling_behavior.hpp"
#include "../behaviors/flowing_behavior.hpp"
#include "../behaviors/heavy_behavior.hpp"
#include "../behaviors/spreading_behavior.hpp"
#include "../behaviors/flaming_behavior.hpp"
#include "../behaviors/flammable_behavior.hpp"
#include "../behaviors/static_behavior.hpp"
#include "../behaviors/burning_behavior.hpp"
#include "../behaviors/cooling_behavior.hpp"
#include "../behaviors/rising_behavior.hpp"

const CellPreset SANDPRESET(sf::Color(252, 191, 98), {std::make_shared<FallingBehavior>(), std::make_shared<HeavyBehavior>(3), std::make_shared<SettlingBehavior>()});
const CellPreset WATERPRESET(sf::Color(19, 94, 186), {std::make_shared<FallingBehavior>(), std::make_shared<HeavyBehavior>(2), std::make_shared<FlowingBehavior>(), std::make_shared<CoolingBehavior>()});
const CellPreset FIREPRESET(sf::Color(255, 0, 0), {std::make_shared<BurningBehavior>(30), std::make_shared<FlamingBehavior>(), std::make_shared<SpreadingBehavior>()});
const CellPreset WOODPRESET(sf::Color(99, 64, 28), {std::make_shared<FlammableBehavior>(100), std::make_shared<StaticBehavior>()});
const CellPreset SMOKEPRESET(sf::Color(55, 55, 55), {std::make_shared<RisingBehavior>(1), std::make_shared<SettlingBehavior>()});

const CellPreset TEMPPRESET(sf::Color(255, 255, 255), {std::make_shared<FallingBehavior>()});

CellManager::CellManager()
{
    presets = {
        {"sand", SANDPRESET},
        {"water", WATERPRESET},
        {"fire", FIREPRESET},
        {"wood", WOODPRESET},
        {"smoke", SMOKEPRESET},
        {"temp", TEMPPRESET}
    };
}