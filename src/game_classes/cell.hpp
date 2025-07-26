#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

#include "../managers/cell_manager.hpp"
#include "../presets/cell_preset.hpp"
#include "grid.hpp"

class Cell
{
public:
    Cell();

    Cell(CellManager* cellManager, Grid* grid, std::vector<std::shared_ptr<Being>>* beings, std::string type, sf::Vector2u position);

    void create(CellManager* cellManager, Grid* grid, std::vector<std::shared_ptr<Being>>* beings, std::string type, sf::Vector2u position);

    bool tick(bool log = false);

    void update();

    void changeVelocity(sf::Vector2i amount);

    void setPos(sf::Vector2u newPos);

    void changePos(sf::Vector2i distance);

    void changeType(std::string newType);

    void addStartBehavior(std::shared_ptr<Behavior> newBehavior);

    void addEndBehavior(std::shared_ptr<Behavior> newBehavior);

    std::string getType();

    sf::Vector2i getVelocity();

    int getOptionalSetting(std::string settingName);

    int getWeight();

    sf::Color getColor();

    bool hasBehavior(std::string behaviorName);
private:
    CellManager* cellManager;

    Grid* grid;
    
    std::vector<std::shared_ptr<Being>>* beings;
    
    std::string type;

    sf::Vector2u position;
    
    sf::Vector2i velocity;

    int weight;

    CellPreset myPreset;
};