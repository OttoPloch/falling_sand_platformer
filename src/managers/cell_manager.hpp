#pragma once

#include <map>

#include "../presets/cell_preset.hpp"

struct CellManager
{
    CellManager();
    
    std::map<std::string, CellPreset> presets;
};