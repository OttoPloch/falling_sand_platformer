#include "world.hpp"

#include "../tools/collision.hpp"

const int GRIDLENGTH = 200;
const int GRIDHEIGHT = 200;

World::World() {}

void World::create(sf::RenderWindow* window)
{
    grid.create(GRIDLENGTH, GRIDHEIGHT, &beings);
    
    resourceManager.load();

    beings.emplace_back(std::make_shared<Being>(sf::Vector2f(200, 300), sf::Vector2f(100, 100), 0, resourceManager.getTexture("moon"), window, &grid));
    beings.emplace_back(std::make_shared<Being>(sf::Vector2f(800, 800), sf::Vector2f(500, 500), -30, resourceManager.getTexture("sun"), window, &grid));

    this->window = window;
}

void World::tick(sf::Vector2u creatorPos)
{
    grid.updateCells(creatorPos);
    
    beings[0]->rotate(3);

    if (beings.size() > 0)
    {
        for (int i = 0; i < beings.size(); i++)
        {
            beings[i]->tick();
        }
    }
}

void World::update(sf::Vector2u creatorPos)
{
    if (beings.size() > 0)
    {
        for (int i = 0; i < beings.size(); i++)
        {
            beings[i]->update();
        }
    }

    // creates a sand cell; temporary for testing
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        makeACell("sand", creatorPos);
    }

    // creates a water cell; temporary for testing
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        makeACell("water", creatorPos);
    }

    // creates a fire cell; temporary for testing
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
    {
        makeACell("fire", creatorPos);
    }

    // creates a wood cell; temporary for testing
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        makeACell("wood", creatorPos);
    }
    
    // creates a smoke cell; temporary for testing
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O))
    {
        makeACell("smoke", creatorPos);
    }

    // delete a cell
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
    {
        deleteACell(creatorPos);
    }
}

void World::draw()
{
    // TEMP
    for (unsigned int i = 0; i < grid.getSize(); i++)
    {
        for (unsigned int j = 0; j < grid.getSizeOfRow(i); j++)
        {
            if (grid.at({j, i}) != nullptr)
            {
                sf::RectangleShape rect({static_cast<float>(getCellSize()), static_cast<float>(getCellSize())});
    
                rect.setFillColor(grid.at({j, i})->getColor());
                rect.setPosition({(float)(j * getCellSize()), (float)(i * getCellSize())});
    
                window->draw(rect);
            }
        }
    }

    if (beings.size() > 0)
    {
        for (int i = 0; i < beings.size(); i++)
        {
            beings[i]->draw();
        }
    }
}

sf::Vector2u World::getGridSize() { return {grid.getSize(), grid.getSizeOfRow(0)}; }

int World::getCellSize() { return grid.getCellSize(); }

int World::getCellCount() { return grid.getCellCount(); }

void World::makeACell(std::string type, sf::Vector2u position) { grid.createCell(&cellManager, type, position); }

void World::deleteACell(sf::Vector2u position) { grid.removeCell(position); }