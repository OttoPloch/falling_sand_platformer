#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "behavior.hpp"
#include "behaviors/falling_behavior.hpp"

struct CellPreset
{
    CellPreset();

    CellPreset(sf::Color color, std::vector<std::shared_ptr<Behavior>> behaviors);
    
    sf::Color color;
    
    std::vector<std::shared_ptr<Behavior>> behaviors;
};