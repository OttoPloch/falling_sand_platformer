#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <iostream>

#include "behavior.hpp"

struct CellPreset
{
    CellPreset();

    CellPreset(sf::Color color,  std::vector<std::shared_ptr<Behavior>> behaviors);
    
    sf::Color color;
    
    std::vector<std::shared_ptr<Behavior>> behaviors;
    
    std::map<std::string, int> optionalSettings;
};