#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "../../game_classes/grid.hpp"
#include "../../tools/get_random_number.hpp"

class Cell;

class Behavior
{
public:
    Behavior(std::string name, int specialAttribute);

    // overridden by child classes, if it succeeds in moving the cell,
    // it returns true. Otherwise, it returns false and the cell moves
    // to the next behavior.
    virtual bool update(CellManager* cellManager, sf::Vector2u gridPos);
    
    // name is set by child classes (e.g. "fall", "flow", etc.)
    std::string getName();

    int getSpecialAttribute();
protected:
    std::string name;

    // this would be like weight or flamability,
    // something that gets passed in the preset constructor
    int specialAttribute;
};