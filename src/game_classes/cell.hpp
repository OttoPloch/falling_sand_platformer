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

    // ptr to this cell, hasChanged
    std::pair<Cell*, bool> tick(bool log = false);

    void changeVelocity(sf::Vector2i amount);

    void setPos(sf::Vector2u newPos);

    void changePos(sf::Vector2i distance);

    void changeType(std::string newType);

    void addStartBehavior(std::shared_ptr<Behavior> newBehavior);

    void addEndBehavior(std::shared_ptr<Behavior> newBehavior);

    // -1 = behavior not found, 0 = one instance and it was deleted, >0 = first instance was deleted and there are x more
    int removeBehavior(std::string behaviorName);

    sf::Vector2u getPosition();

    std::string getType();

    sf::Vector2i getVelocity();

    int getOptionalSetting(std::string settingName);

    float getWeight();

    int getWeightCounterInt();

    int incrementWeightCounter();

    int decrementWeightCounter();

    int getWaterLevel();

    void addToWaterLevel(int amount);

    sf::Color getColor();

    bool hasBehavior(std::string behaviorName);

    bool canSmooth();
private:
    CellManager* cellManager;

    Grid* grid;
    
    std::vector<std::shared_ptr<Being>>* beings;
    
    std::string type;

    sf::Vector2u position;
    
    sf::Vector2i velocity;

    float weight;

    // if weight has a decimal, this gets incremented to add more precision
    float weightCounter;

    // for plant-related behaviors
    int waterLevel;

    CellPreset myPreset;
};