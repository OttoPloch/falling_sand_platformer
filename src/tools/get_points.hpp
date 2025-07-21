#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>

// A rotation of zero will make the point go straight up.
// The rotation continues clockwise.
sf::Vector2f getRotatedPoint(sf::Vector2f point, float distance, float rotation);

sf::Vector2f getRectTopLeft(sf::Vector2f center, sf::Vector2f size, float rotation);