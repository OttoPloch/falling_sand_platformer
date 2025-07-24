#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "grid.hpp"

class Being
{
public:
    Being();

    Being(sf::Vector2f position, sf::Vector2f size, float rotation, sf::Texture* texture, sf::RenderWindow* window, Grid* grid);

    void create(sf::Vector2f position, sf::Vector2f size, float rotation, sf::Texture* texture, sf::RenderWindow* window, Grid* grid);

    sf::Vector2f getPosition();

    sf::Vector2f getSize();

    float getRotation();

    void move(sf::Vector2f amount);

    void move(float xAmount, float yAmount);

    void rotate(float amount);

    void tick();

    void update();

    void draw();
private:
    sf::Vector2f position;

    sf::Vector2f velocity;

    sf::Vector2f acceleration;
    
    float rotation;

    float rotationalVelocity;

    float rotationalAcceleration;

    sf::Vector2f size;

    sf::Texture* texture;

    std::shared_ptr<sf::Sprite> sprite;

    sf::RenderWindow* window;

    Grid* grid;

    void spriteInit();

    void forcesInit();
};