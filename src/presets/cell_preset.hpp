#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <iostream>

#include "../behaviors/base/behavior.hpp"

struct CellPreset
{
    CellPreset();

    CellPreset(int weight, sf::Color color, std::vector<std::shared_ptr<Behavior>> behaviors);
    
    int weight;

    sf::Color color;
    
    std::vector<std::shared_ptr<Behavior>> behaviors;
    
    std::map<std::string, int> optionalSettings;
};