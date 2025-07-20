#include "being.hpp"

Being::Being() : position({0.f, 0.f}), velocity({0.f, 0.f}), rotation(0.f) {}

Being::Being(sf::Vector2f position, sf::Vector2f size, float rotation, sf::Texture* myTexture, sf::RenderWindow* window)
{
    create(position, size, rotation, texture, window);
}

void Being::create(sf::Vector2f position, sf::Vector2f size, float rotation, sf::Texture *texture, sf::RenderWindow* window)
{
    this->position = position;
    this->rotation = rotation;
    this->texture = texture;
    this->window = window;

    velocity = {1.f, 0.f};

    spriteInit(size);
}

void Being::spriteInit(sf::Vector2f size)
{
    sprite = std::make_shared<sf::Sprite>(*texture);
    sprite->setScale({size.x / sprite->getTexture().getSize().x, size.y / sprite->getTexture().getSize().y});
    sprite->setOrigin(sprite->getLocalBounds().getCenter());
    sprite->setPosition(position);
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