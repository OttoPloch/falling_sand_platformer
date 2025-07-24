#pragma once

#include <map>
#include <SFML/Graphics.hpp>

#include "../presets/cell_preset.hpp"
#include "../game_classes/grid.hpp"

struct CellManager
{
    CellManager();

    CellManager(float cellSize, sf::Vector2f cellOffset, Grid* grid);

    std::map<std::string, CellPreset> presets;

    Grid* grid;
    
    float cellSize;
    
    sf::Vector2f cellOffset;
    
    sf::Vector2f beingRectInflationSize;
};