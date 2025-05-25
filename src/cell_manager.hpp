#pragma once

#include <map>

#include "cell_preset.hpp"
#include "behaviors/falling_behavior.hpp"
#include "behaviors/settling_behavior.hpp"
#include "behaviors/flowing_behavior.hpp"

struct CellManager
{
    CellManager();
    
    std::map<std::string, CellPreset> presets;
};