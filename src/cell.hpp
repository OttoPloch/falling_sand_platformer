#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

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

    void changeType(std::string newType);

    void addStartBehavior(std::shared_ptr<Behavior> newBehavior);

    void addEndBehavior(std::shared_ptr<Behavior> newBehavior);

    std::string getType();

    int getOptionalSetting(std::string settingName);

    sf::Color getColor();

    bool hasBehavior(std::string behaviorName);
private:
    CellManager* cellManager;

    Grid* grid;
    
    std::string type;

    sf::Vector2u position;

    CellPreset myPreset;
};