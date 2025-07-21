#include "world.hpp"

World::World() {}

void World::create(int gridLength, int gridHeight, sf::RenderWindow* window)
{
    grid.create(gridLength, gridHeight);

    resourceManager.load();

    moon.create({300, 300}, {100, 100}, 0, resourceManager.getTexture("moon"), window, &grid);
    sun.create({500, 800}, {500, 500}, 0, resourceManager.getTexture("sun"), window, &grid);

    this->window = window;
}

void World::tick(sf::Vector2u creatorPos)
{
    grid.updateCells(creatorPos);

    moon.rotate(1);
    sun.rotate(1);
    
    moon.tick();
    sun.tick();
}

void World::update(sf::Vector2u creatorPos)
{
    moon.update();
    sun.update();

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

    moon.draw();
    sun.draw();

    // TEMP
    std::vector<std::vector<sf::Vector2f>> moonPoints = moon.getAlignedPoints();

    for (int y = 0; y < moonPoints.size(); y++)
    {
        for (int x = 0; x < moonPoints[y].size(); x++)
        {
            sf::RectangleShape rect({static_cast<float>(getCellSize()), static_cast<float>(getCellSize())});
            rect.setFillColor(sf::Color::Transparent);
            rect.setOutlineColor(sf::Color::Red);
            rect.setOutlineThickness(1.f);
            //rect.setOrigin(rect.getLocalBounds().getCenter());
            rect.setPosition(moonPoints[y][x]);
            rect.setRotation(sf::degrees(moon.getRotation()));
            window->draw(rect);
        }
    }

    // TEMP
    std::vector<std::vector<sf::Vector2f>> sunPoints = sun.getAlignedPoints();

    for (int y = 0; y < sunPoints.size(); y++)
    {
        for (int x = 0; x < sunPoints[y].size(); x++)
        {
            sf::RectangleShape rect({static_cast<float>(getCellSize()), static_cast<float>(getCellSize())});
            rect.setFillColor(sf::Color::Transparent);
            rect.setOutlineColor(sf::Color::Red);
            rect.setOutlineThickness(1.f);
            //rect.setOrigin(rect.getLocalBounds().getCenter());
            rect.setPosition(sunPoints[y][x]);
            rect.setRotation(sf::degrees(sun.getRotation()));
            window->draw(rect);
        }
    }
}

sf::Vector2u World::getGridSize() { return {grid.getSize(), grid.getSizeOfRow(0)}; }

int World::getCellSize() { return grid.getCellSize(); }

int World::getCellCount() { return grid.getCellCount(); }

void World::makeACell(std::string type, sf::Vector2u position)
{
    grid.createCell(&cellManager, &grid, type, position);
}

void World::deleteACell(sf::Vector2u position)
{
    grid.removeCell(position);
}