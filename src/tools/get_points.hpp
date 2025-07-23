#pragma once

#include <SFML/Graphics.hpp>

// A rotation of zero will make the point go straight up.
// The rotation continues clockwise.
sf::Vector2f getRotatedPoint(sf::Vector2f point, float distance, float rotation);

sf::Vector2f rotateAroundPoint(sf::Vector2f point, sf::Vector2f origin, float rotationAmount);

sf::Vector2f getRectCorner(sf::Vector2f center, sf::Vector2f offset, float rotation);

sf::FloatRect getRectBoundingBox(int cellSize, sf::Vector2f cellOffset, sf::Vector2f center, sf::Vector2f size, float rotation, bool asGridCoords);

// This returns a point for every spot in a rectangle where a cell could go.
// If asGridCoords is true, the points will be aligned to the Grid
std::vector<sf::Vector2f> getRectAlignedPoints(int cellSize, sf::Vector2f cellOffset, sf::Vector2f center, sf::Vector2f size, float rotation, bool asGridCoords);

// If convertCenter is true, then the returned point will be where the center of the grid Coord is,
// otherwise it will be the top left.
sf::Vector2f gridToWorldCoords(int cellSize, sf::Vector2f cellOffset, sf::Vector2u gridCoord, bool convertCenter);

sf::Vector2u worldToGridCoords(int cellSize, sf::Vector2f cellOffset, sf::Vector2f worldCoord);