#include "world.hpp"

World::World() {}

void World::create(int gridLength, int gridHeight, sf::RenderWindow* window)
{
    grid.create(gridLength, gridHeight);

    this->window = window;
}

void World::update(sf::Vector2u creatorPos)
{
    grid.updateCells(creatorPos);
}

void World::draw()
{
    for (unsigned int i = 0; i < grid.getSize(); i++)
    {
        for (unsigned int j = 0; j < grid.getSizeOfRow(i); j++)
        {
            if (grid.at({j, i}) != nullptr)
            {
                sf::RectangleShape rect({30.f, 30.f});
    
                rect.setFillColor(grid.at({j, i})->getColor());
                rect.setPosition({(float)(j * 30), (float)(i * 30)});
    
                window->draw(rect);
            }
        }
    }
}

sf::Vector2u World::getGridSize() { return {grid.getSize(), grid.getSizeOfRow(0)}; }

sf::Vector2u World::getCellSize() { return grid.getCellSize(); }

int World::getCellCount() { return grid.getCellCount(); }

void World::makeACell(std::string type, sf::Vector2u position)
{
    grid.createCell(&cellManager, &grid, type, position);
}

void World::deleteACell(sf::Vector2u position)
{
    grid.removeCell(position);
}