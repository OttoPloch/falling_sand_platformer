#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <iostream>

#include "../behaviors/base/behavior.hpp"

struct CellPreset
{
    CellPreset();

    CellPreset(float weight, bool canSmooth, sf::Color color, std::vector<std::shared_ptr<Behavior>> behaviors);
    
    float weight;

    // Whether or not the grid can use moving cells to interpolate.
    // This needs to be disabled for things like fire that move rapidly
    bool canSmooth;

    sf::Color color;
    
    std::vector<std::shared_ptr<Behavior>> behaviors;
    
    std::map<std::string, int> optionalSettings;
};