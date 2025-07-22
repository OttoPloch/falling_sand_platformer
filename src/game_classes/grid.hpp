#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "../tools/get_random_number.hpp"

class Cell;
class CellManager;
class Being;

class Grid
{
public:
    Grid();

    Grid(unsigned int gridLength, unsigned int gridHeight);

    void create(unsigned int gridLength, unsigned int gridHeight);

    // returns a pointer to the cell at the given position
    Cell* at(sf::Vector2u position);

    // gets the size/height of the grid
    unsigned int getSize();

    // gets the width of the grid at a specific row,
    // though I doubt a non-rectangular grid will happen
    unsigned int getSizeOfRow(unsigned int rowIndex);

    // returns the length of cells in the grid
    int getCellSize();

    // returns the offset that cells will be placed at in the world
    sf::Vector2i getCellOffset();

    // gets the current amount of cells on the grid
    unsigned int getCellCount();
    
    // creates the cells that a being uses to interact with the grid
    void makeBeingCells(Being* being, std::vector<sf::Vector2f> points, std::string cellType, CellManager* cellManager, Grid* grid);

    // makes the cell, no checks other than for nullptr
    void createCell(CellManager* cellManager, Grid* grid, std::string type, sf::Vector2u position, bool fromBeing);

    // removes a cell from the grid
    void removeCell(sf::Vector2u gridPos);

    // moves a cell a given distance, no checks other than for nullptr and bounds.
    // if success, return true else return false
    bool moveCell(sf::Vector2u gridPos, sf::Vector2i distance);

    // swaps two cells
    void swap(sf::Vector2u gridPos1, sf::Vector2u gridPos2);

    // iterates through the grid and updates cells
    void updateCells(sf::Vector2u creatorPos);
private:
    std::vector<std::vector<std::shared_ptr<Cell>>> theGrid;

    std::vector<sf::Vector2u> beingCells;
};