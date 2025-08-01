#include "being.hpp"

#include <iostream>
#include "../tools/get_points.hpp"
#include <cmath>

Being::Being() : position({0.f, 0.f}), velocity({0.f, 0.f}), acceleration({0.f, 0.f}), rotation(0.f), rotationalVelocity(0.f), rotationalAcceleration(0.f) {}

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
    forcesInit();
}

void Being::spriteInit()
{
    sprite = std::make_shared<sf::Sprite>(*texture);
    sprite->setScale({size.x / sprite->getTexture().getSize().x, size.y / sprite->getTexture().getSize().y});
    sprite->setOrigin(sprite->getLocalBounds().getCenter());
    sprite->setPosition(position);
    sprite->setRotation(sf::degrees(rotation));
}

void Being::forcesInit()
{
    velocity = {0, 0};
    acceleration = {0, 0};
    rotationalVelocity = 0.f;
    rotationalAcceleration = 0.f;
}

sf::Vector2f Being::getPosition() { return position; }

sf::Vector2f Being::getSize() { return size; }

float Being::getRotation() { return rotation; }

void Being::move(sf::Vector2f amount) { position = {position.x + amount.x, position.y + amount.y}; }

void Being::move(float xAmount, float yAmount) { position = {position.x + xAmount, position.y + yAmount}; }

void Being::rotate(float amount)
{
    rotation = std::fmod(rotation + amount, 360.f);
}

void Being::tick()
{
    velocity.x += acceleration.x;
    velocity.y += acceleration.y;

    position.x += velocity.x;
    position.y += velocity.y;

    rotationalVelocity += rotationalAcceleration;

    rotation += rotationalVelocity;
}

void Being::update()
{
    // TODO: Replace with interpolation
    sprite->setPosition(position);
    sprite->setRotation(sf::degrees(rotation));
}

void Being::draw(sf::RenderStates& states)
{
    window->draw(*sprite, states);
}