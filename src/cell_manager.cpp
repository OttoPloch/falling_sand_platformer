#include "cell_manager.hpp"

const CellPreset SANDPRESET(sf::Color(252, 191, 98), 3, {std::make_shared<FallingBehavior>(), std::make_shared<HeavyBehavior>(), std::make_shared<SettlingBehavior>()});
const CellPreset WATERPRESET(sf::Color(19, 94, 186), 2, {std::make_shared<FallingBehavior>(), std::make_shared<HeavyBehavior>(), std::make_shared<FlowingBehavior>()});

CellManager::CellManager()
{
    presets = {
        {"sand", SANDPRESET},
        {"water", WATERPRESET}
    };
}