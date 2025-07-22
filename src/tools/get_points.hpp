#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <algorithm>

// A rotation of zero will make the point go straight up.
// The rotation continues clockwise.
sf::Vector2f getRotatedPoint(sf::Vector2f point, float distance, float rotation);

sf::Vector2f getRectTopLeft(sf::Vector2f center, sf::Vector2f size, float rotation);

// This returns a point for every spot in a rectangle where a cell could go.
// If asGridCoords is true, the points will be aligned to the Grid
std::vector<sf::Vector2f> getRectAlignedPoints(int cellSize, sf::Vector2i cellOffset, sf::Vector2f center, sf::Vector2f size, float rotation, bool asGridCoords);