#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <memory>

class Being
{
public:
    Being();

    Being(sf::Vector2f position, sf::Vector2f size, float rotation, sf::Texture* myTexture, sf::RenderWindow* window);

    void create(sf::Vector2f position, sf::Vector2f size, float rotation, sf::Texture* myTexture, sf::RenderWindow* window);

    void tick();

    void update();

    void draw();

private:
    sf::Vector2f position;

    sf::Vector2f velocity;
    
    float rotation;

    sf::Texture* texture;

    std::shared_ptr<sf::Sprite> sprite;

    sf::RenderWindow* window;

    void spriteInit(sf::Vector2f size);
};