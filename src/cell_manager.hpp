#pragma once

#include <map>

#include "cell_preset.hpp"
#include "behaviors/falling_behavior.hpp"
#include "behaviors/settling_behavior.hpp"
#include "behaviors/flowing_behavior.hpp"
#include "behaviors/heavy_behavior.hpp"
#include "behaviors/spreading_behavior.hpp"
#include "behaviors/flaming_behavior.hpp"
#include "behaviors/flammable_behavior.hpp"
#include "behaviors/static_behavior.hpp"
#include "behaviors/burning_behavior.hpp"
#include "behaviors/cooling_behavior.hpp"

struct CellManager
{
    CellManager();
    
    std::map<std::string, CellPreset> presets;
};