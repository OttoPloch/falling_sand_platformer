#pragma once

#include <SFML/Graphics.hpp>

class CellManager;
class Grid;
class Cell;

class GridVertices
{
public:
    GridVertices();

    GridVertices(int gridLength, int gridHeight, CellManager* cellManager);

    void init();

    void updateSquare(unsigned int x, unsigned int y);

    void updateStatic();

    void updateMoving();

    void draw(sf::RenderWindow& window);

    void addMovingCell(unsigned int x, unsigned int y, sf::Vector2u targetPos, Cell* cell);
private:
    int gridLength;

    int gridHeight;

    CellManager* cellManager;

    Grid* grid;

    sf::VertexArray vertices;

    sf::RenderStates states;

    // vector of tuples -> (6 vertices for a square, vector of target GRID positions, ptr of a Cell)
    std::vector<std::tuple<std::array<sf::Vertex, 6>, std::vector<sf::Vector2u>, Cell*>> movingCells;
};