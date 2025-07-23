#include "being.hpp"

#include <iostream>
#include "../tools/get_points.hpp"
#include <cmath>

Being::Being() : position({0.f, 0.f}), velocity({0.f, 0.f}), rotation(0.f) {}

Being::Being(sf::Vector2f position, sf::Vector2f size, float rotation, sf::Texture* texture, sf::RenderWindow* window, Grid* grid)
{
    create(position, size, rotation, texture, window, grid);
}

void Being::create(sf::Vector2f position, sf::Vector2f size, float rotation, sf::Texture*texture, sf::RenderWindow* window, Grid* grid)
{
    this->position = position;
    this->size = size;
    this->rotation = rotation;
    this->texture = texture;
    this->window = window;
    this->grid = grid;

    spriteInit();
}

void Being::spriteInit()
{
    sprite = std::make_shared<sf::Sprite>(*texture);
    sprite->setScale({size.x / sprite->getTexture().getSize().x, size.y / sprite->getTexture().getSize().y});
    sprite->setOrigin(sprite->getLocalBounds().getCenter());
    sprite->setPosition(position);
    sprite->setRotation(sf::degrees(rotation));
}

sf::Vector2f Being::getPosition() { return position; }

sf::Vector2f Being::getSize() { return size; }

float Being::getRotation() { return rotation; }

void Being::move(sf::Vector2f amount) { position = {position.x + amount.x, position.y + amount.y}; }

void Being::move(float xAmount, float yAmount) { position = {position.x + xAmount, position.y + yAmount}; }

void Being::rotate(float amount)
{
    rotation += amount;

    if (rotation > 360.f) std::fmod(rotation, 360.f);

    sprite->setRotation(sf::degrees(rotation));
}

void Being::tick()
{
    position.x += velocity.x;
    position.y += velocity.y;
}

void Being::update()
{
    sprite->setPosition(position);
}

void Being::draw()
{
    window->draw(*sprite);
}