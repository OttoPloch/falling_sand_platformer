#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "behavior.hpp"

struct CellPreset
{
    CellPreset();

    CellPreset(sf::Color color, int weight, std::vector<std::shared_ptr<Behavior>> behaviors);
    
    sf::Color color;
    
    int weight;
    
    std::vector<std::shared_ptr<Behavior>> behaviors;
};