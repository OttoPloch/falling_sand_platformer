#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "grid_vertices.hpp"

class Cell;
class CellManager;
class Being;

class Grid
{
public:
    Grid();

    Grid(unsigned int gridLength, unsigned int gridHeight, std::vector<std::shared_ptr<Being>>* beings, CellManager* cellManager);

    void create(unsigned int gridLength, unsigned int gridHeight, std::vector<std::shared_ptr<Being>>* beings, CellManager* cellManager);

    // returns a pointer to the cell at the given position
    Cell* at(sf::Vector2u position);

    unsigned int getLength();

    unsigned int getHeight();

    // gets the current amount of cells on the grid
    unsigned int getCellCount();
    
    // increments the plantIDMaker and returns the old value
    int getNewPlantID();

    // Fills an area with cells where a being is located
    // (as of right now, this doesn't exist, but i plan to add a toggle for beings that turn off their cell interaction,
    // which would be the only case that this could be used since otherwise there would be no valid spaces to make cells)
    void makeCellsFromBeing(Being* being, std::string cellType);

    // Just checking if a cell can move to another location
    bool canMoveTo(sf::Vector2u from, sf::Vector2u to);

    // Same as canMoveTo, but takes a distance
    bool canMoveDistance(sf::Vector2u from, sf::Vector2i distance);

    // makes the cell, no checks other than for nullptr and beings
    void createCell(std::string type, sf::Vector2u position, unsigned int plantID = 0);

    // removes a cell from the grid
    void removeCell(sf::Vector2u gridPos);

    // moves a cell a given distance, make sure all checks are done beforehand.
    void moveCell(sf::Vector2u gridPos, sf::Vector2i distance);

    // swaps two cells
    void swap(sf::Vector2u gridPos1, sf::Vector2u gridPos2);

    // iterates through the grid and updates cells
    void tick(sf::Vector2u creatorPos);

    // updates a single cell, returns whether or not a change occured
    bool tickCell(sf::Vector2u position);

    void update(float dt);

    // this actually draws the grid, believe it or not
    void draw(sf::RenderWindow& window, sf::RenderStates& states);
private:
    int gridLength, gridHeight;

    std::vector<std::vector<std::shared_ptr<Cell>>> theGrid;

    std::vector<std::shared_ptr<Being>>* beings;

    CellManager* cellManager;

    GridVertices gridVertices;

    unsigned int plantIDMaker;
};