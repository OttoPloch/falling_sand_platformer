#include "world.hpp"

const int GRIDLENGTH = 100;
const int GRIDHEIGHT = 100;

World::World() {}

void World::create(sf::RenderWindow* window)
{
    grid.create(GRIDLENGTH, GRIDHEIGHT);

    resourceManager.load();

    moon.create({200, 300}, {100, 100}, 0, resourceManager.getTexture("moon"), window, &grid);
    sun.create({500, 800}, {300, 300}, 0, resourceManager.getTexture("sun"), window, &grid);

    this->window = window;
}

void World::tick(sf::Vector2u creatorPos)
{
    grid.updateCells(creatorPos);
    
    grid.makeBeingCells(&moon, moon.getAlignedPoints(true), "being", &cellManager, &grid);
    grid.makeBeingCells(&sun, sun.getAlignedPoints(true), "being", &cellManager, &grid);
    
    sun.rotate(3);

    moon.move(1, 0);
    sun.move(1, 0);

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

    // // TEMP
    // std::vector<sf::Vector2f> moonPoints = moon.getAlignedPoints(false);

    // for (int i = 0; i < moonPoints.size(); i++)
    // {
    //     if (std::fmod(moonPoints[i].x, getCellSize()) > 0.001f || std::fmod(moonPoints[i].y, getCellSize()) > 0.001f)
    //     {
    //         std::cout << abs(std::fmod(moonPoints[i].x, getCellSize()) - getCellSize()) << '\n';
    //     }

    //     // sf::CircleShape circle(2.f);
    //     // circle.setFillColor(sf::Color::Red);
    //     // circle.setOrigin({2.f, 2.f});
    //     // circle.setPosition(moonPoints[i]);
    //     // window->draw(circle);

    //     sf::RectangleShape rect({static_cast<float>(getCellSize()), static_cast<float>(getCellSize())});
    //     rect.setFillColor(sf::Color(255, 0, 0, 50));
    //     // rect.setOutlineColor(sf::Color::Red);
    //     // rect.setOutlineThickness(1.f);
    //     //rect.setOrigin(rect.getLocalBounds().getCenter());
    //     rect.setPosition(moonPoints[i]);
    //     //rect.setRotation(sf::degrees(moon.getRotation()));
    //     window->draw(rect);
    // }

    // // TEMP
    // std::vector<sf::Vector2f> sunPoints = sun.getAlignedPoints(false);

    // for (int i = 0; i < sunPoints.size(); i++)
    // {
    //     // sf::CircleShape circle(5.f);
    //     // circle.setFillColor(sf::Color::Red);
    //     // circle.setOrigin({5.f, 5.f});
    //     // circle.setPosition(sunPoints[i]);
    //     // window->draw(circle);

    //     sf::RectangleShape rect({static_cast<float>(getCellSize()), static_cast<float>(getCellSize())});
    //     rect.setFillColor(sf::Color(255, 0, 0, 50));
    //     // rect.setOutlineColor(sf::Color::Red);
    //     // rect.setOutlineThickness(1.f);
    //     //rect.setOrigin(rect.getLocalBounds().getCenter());
    //     rect.setPosition(sunPoints[i]);
    //     //rect.setRotation(sf::degrees(sun.getRotation()));
    //     window->draw(rect);
    // }
}

sf::Vector2u World::getGridSize() { return {grid.getSize(), grid.getSizeOfRow(0)}; }

int World::getCellSize() { return grid.getCellSize(); }

int World::getCellCount() { return grid.getCellCount(); }

void World::makeACell(std::string type, sf::Vector2u position) { grid.createCell(&cellManager, &grid, type, position, false); }

void World::deleteACell(sf::Vector2u position) { grid.removeCell(position); }