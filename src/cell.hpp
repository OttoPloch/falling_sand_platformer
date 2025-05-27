#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "cell_manager.hpp"
#include "cell_preset.hpp"
#include "grid.hpp"

class Cell
{
public:
    Cell();

    Cell(CellManager* cellManager, Grid* grid, std::string type, sf::Vector2u position);

    void create(CellManager* cellManager, Grid* grid, std::string type, sf::Vector2u position);

    void update();

    void setPos(sf::Vector2u newPos);

    void changePos(sf::Vector2i distance);

    std::string getType();

    int getWeight();

    sf::Color getColor();

    bool hasBehavior(std::string behaviorName);
private:
    CellManager* cellManager;

    Grid* grid;
    
    std::string type;

    sf::Vector2u position;

    CellPreset myPreset;
};