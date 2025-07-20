#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "cell.hpp"
#include "./tools/get_random_number.hpp"
#include "./managers/cell_manager.hpp"
#include "grid.hpp"
#include "being.hpp"
#include "./managers/resource_manager.hpp"

class World
{
public:
    // temp
    Being moon;
    Being sun;

    World();

    void create(int gridLength, int gridHeight, sf::RenderWindow* window);

    void tick(sf::Vector2u creatorPos);
    
    void update(sf::Vector2u creatorPos);

    void draw();

    sf::Vector2u getGridSize();

    sf::Vector2u getCellSize();

    int getCellCount();

    void makeACell(std::string type, sf::Vector2u position);

    void deleteACell(sf::Vector2u position);
private:
    sf::RenderWindow* window;
    
    CellManager cellManager;

    ResourceManager resourceManager;
    
    Grid grid;
};