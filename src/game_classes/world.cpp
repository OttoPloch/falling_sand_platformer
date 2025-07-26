#include "world.hpp"

#include "cell.hpp"
#include "../tools/get_random_number.hpp"
#include "../tools/collision.hpp"
#include "../tools/get_points.hpp"

const int GRIDLENGTH = 100;
const int GRIDHEIGHT = 100;

const float CELLSIZE = 10;

const float CELLOFFSETX = 0;
const float CELLOFFSETY = 0;

World::World() {}

void World::create(sf::RenderWindow* window)
{
    cellManager = CellManager(CELLSIZE, {CELLOFFSETX, CELLOFFSETY}, &grid, &beings);

    grid.create(GRIDLENGTH, GRIDHEIGHT, &beings, &cellManager);
    
    resourceManager.load();

    //beings.emplace_back(std::make_shared<Being>(sf::Vector2f(200, 300), sf::Vector2f(100, 100), 0, resourceManager.getTexture("moon"), window, &grid));
    //beings.emplace_back(std::make_shared<Being>(sf::Vector2f(800, 800), sf::Vector2f(500, 500), -30, resourceManager.getTexture("sun"), window, &grid));

    this->window = window;
}

void World::tick(sf::Vector2u creatorPos)
{
    grid.updateCells(creatorPos);
    
    //beings[0]->rotate(3);
    //beings[1]->move({0, 1});

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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) makeACell("temp", creatorPos);

    // delete a cell
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
    {
        deleteACell(creatorPos);
    }
}

void World::draw()
{
    grid.draw(*window);

    if (beings.size() > 0)
    {
        for (int i = 0; i < beings.size(); i++)
        {
            beings[i]->draw();

            if (i != -1)
            {
                std::vector<sf::Vector2f> points = getRectAlignedPoints(&cellManager, beings[i]->getPosition(), beings[i]->getSize(), beings[i]->getRotation(), false);
                
                for (int j = 0; j < points.size(); j++)
                {
                    sf::RectangleShape rect({CELLSIZE, CELLSIZE});
    
                    rect.setFillColor(sf::Color(255, 0, 0, 100));
                    rect.setPosition(points[j]);
                    
                    window->draw(rect);
                }
            }
        }
    }
}

sf::Vector2u World::getGridSize() { return {grid.getSize(), grid.getSizeOfRow(0)}; }

float World::getCellSize() { return CELLSIZE; }

int World::getCellCount() { return grid.getCellCount(); }

void World::makeACell(std::string type, sf::Vector2u position) { grid.createCell(type, position); }

void World::deleteACell(sf::Vector2u position) { grid.removeCell(position); }