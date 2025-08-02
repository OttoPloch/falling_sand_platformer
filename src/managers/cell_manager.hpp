#pragma once

#include <map>
#include <SFML/Graphics.hpp>

#include "../presets/cell_preset.hpp"
#include "../game_classes/grid.hpp"
#include "../game_classes/being.hpp"
#include "plant_manager.hpp"

struct CellManager
{
    CellManager();

    CellManager(float cellSize, sf::Vector2f cellOffset, Grid* grid, std::vector<std::shared_ptr<Being>>* beings, PlantManager* plantManager);

    std::map<std::string, CellPreset> presets;

    Grid* grid;
    
    // This is here for passing this to functions that already take a CellManager*
    std::vector<std::shared_ptr<Being>>* beings;

    float cellSize;
    
    sf::Vector2f cellOffset;
    
    sf::Vector2f beingRectInflationSize;

    // x/1000 chance that a plant will grow straight up when other options are valid
    int plantGrowUpChance;

    PlantManager* plantManager;
};