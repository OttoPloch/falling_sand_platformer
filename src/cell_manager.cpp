#include "cell_manager.hpp"

const CellPreset SANDPRESET(sf::Color(252, 191, 98), {std::make_shared<FallingBehavior>(), std::make_shared<SettlingBehavior>()});
const CellPreset WATERPRESET(sf::Color(19, 94, 186), {std::make_shared<FallingBehavior>(), std::make_shared<FlowingBehavior>()});

CellManager::CellManager()
{
    presets = {
        {"sand", SANDPRESET},
        {"water", WATERPRESET}
    };
}