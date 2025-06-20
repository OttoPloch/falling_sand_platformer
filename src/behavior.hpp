#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "grid.hpp"
#include "get_random_number.hpp"

class Cell;

struct Behavior
{
    Behavior(std::string name, int specialAttribute);

    // overridden by child classes, if it succeeds in moving the cell,
    // it returns true. Otherwise, it returns false and the cell moves
    // to the next behavior.
    virtual bool update(Grid* grid, sf::Vector2u gridPos);
    
    // name is set by child classes (e.g. "fall", "flow", etc.)
    std::string getName();

    int getSpecialAttribute();
protected:
    std::string name;

    // this would be like weight or flamability,
    // something that gets passed in the preset constructor
    int specialAttribute;
};