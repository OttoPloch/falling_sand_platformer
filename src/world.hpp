#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "cell.hpp"
#include "get_random_number.hpp"
#include "cell_manager.hpp"
#include "grid.hpp"

class World
{
public:
    World();

    void create(int gridLength, int gridHeight, sf::RenderWindow* window);

    void update();    

    void draw();

    sf::Vector2u getGridSize();

    int getCellCount();

    void makeACell(std::string type, sf::Vector2u position);
private:
    sf::RenderWindow* window;

    CellManager cellManager;

    Grid grid;
};