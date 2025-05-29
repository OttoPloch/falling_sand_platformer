#include "cell_manager.hpp"

const CellPreset SANDPRESET(sf::Color(252, 191, 98), {std::make_shared<FallingBehavior>(), std::make_shared<HeavyBehavior>(3), std::make_shared<SettlingBehavior>()});
const CellPreset WATERPRESET(sf::Color(19, 94, 186), {std::make_shared<FallingBehavior>(), std::make_shared<HeavyBehavior>(2), std::make_shared<FlowingBehavior>()});
const CellPreset FIREPRESET(sf::Color(255, 0, 0), {std::make_shared<FlamingBehavior>()});

CellManager::CellManager()
{
    presets = {
        {"sand", SANDPRESET},
        {"water", WATERPRESET},
        {"fire", FIREPRESET}
    };
}