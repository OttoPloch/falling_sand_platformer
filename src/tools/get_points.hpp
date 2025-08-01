#pragma once

#include <SFML/Graphics.hpp>

#include "../managers/cell_manager.hpp"

// A rotation of zero will make the point go straight up.
// The rotation continues clockwise.
sf::Vector2f getRotatedPoint(sf::Vector2f point, float distance, float rotation);

sf::Vector2f rotateAroundPoint(sf::Vector2f point, sf::Vector2f origin, float rotation);

sf::Vector2f getRectCorner(sf::Vector2f center, sf::Vector2f offset, float rotation);

sf::FloatRect getRectBoundingBox(CellManager* cellManager, sf::Vector2f center, sf::Vector2f size, float rotation, bool asGridCoords);

// This returns a point for every spot in a rectangle where a cell could go.
// If asGridCoords is true, the points will be aligned to the Grid
std::vector<sf::Vector2f> getRectAlignedPoints(CellManager* cellManager, sf::Vector2f center, sf::Vector2f size, float rotation, bool asGridCoords);

// If convertCenter is true, then the returned point will be where the center of the grid Coord is,
// otherwise it will be the top left.
// We allow negative grid Coords in case this is not reffering to real grid coords, just aligned positions.
sf::Vector2f gridToWorldCoords(CellManager* cellManager, sf::Vector2i gridCoord, bool convertCenter);

sf::Vector2f gridToWorldCoords(CellManager* cellManager, sf::Vector2u gridCoord, bool convertCenter);

sf::Vector2u worldToGridCoords(CellManager* cellManager, sf::Vector2f worldCoord);

float getDistance(sf::Vector2i vector);

float getDistance(sf::Vector2f vector);

float getDistance(sf::Vector2f vector1, sf::Vector2f vector2);

float getDistance(sf::Vector2i vector1, sf::Vector2i vector2);

// Up is considered 0, and it continues clockwise
float getRotation(sf::Vector2i vector);