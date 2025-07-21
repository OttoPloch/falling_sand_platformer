#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <memory>

#include "grid.hpp"
#include "../tools/get_points.hpp"

class Being
{
public:
    Being();

    Being(sf::Vector2f position, sf::Vector2f size, float rotation, sf::Texture* myTexture, sf::RenderWindow* window, Grid* grid);

    void create(sf::Vector2f position, sf::Vector2f size, float rotation, sf::Texture* myTexture, sf::RenderWindow* window, Grid* grid);

    std::vector<std::vector<sf::Vector2f>> getAlignedPoints();

    float getRotation();

    void rotate(float amount);

    void tick();

    void update();

    void draw();
private:
    sf::Vector2f position;

    sf::Vector2f velocity;
    
    float rotation;

    sf::Vector2f size;

    sf::Texture* texture;

    std::shared_ptr<sf::Sprite> sprite;

    sf::RenderWindow* window;

    Grid* grid;

    void spriteInit();
};