#include "world.hpp"

World::World() {}

void World::create(int gridLength, int gridHeight)
{
    grid.create(gridLength, gridHeight);
}

void World::update()
{
    grid.updateCells();
}

sf::Vector2u World::getGridSize() { return {grid.getSize(), grid.getSizeOfRow(0)}; }

int World::getCellCount() { return grid.getCellCount(); }

void World::makeACell(std::string type, sf::Vector2u position)
{
    grid.createCell(&cellManager, &grid, type, position);
}