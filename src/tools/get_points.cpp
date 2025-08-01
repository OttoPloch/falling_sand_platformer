#include "get_points.hpp"

#include <cmath>
#include <iostream>
#include <algorithm>

#include "collision.hpp"

sf::Vector2f getRotatedPoint(sf::Vector2f point, float distance, float rotation)
{
    float theta = rotation * (3.1415926535f / 180.f);

    float rx = point.x + distance * std::sin(theta);
    float ry = point.y - distance * std::cos(theta);

    if (abs(rx) < 0.0001f) rx = 0;
    if (abs(ry) < 0.0001f) ry = 0;

    return {rx, ry};
}

sf::Vector2f rotateAroundPoint(sf::Vector2f point, sf::Vector2f origin, float rotation)
{
    float theta = rotation * (3.1415926535f / 180.f);

    sf::Vector2f translated;

    translated.x = point.x - origin.x;
    translated.y = point.y - origin.y;

    float x = translated.x * std::cos(theta) - translated.y * std::sin(theta);
    float y = translated.x * std::sin(theta) + translated.y * std::cos(theta);

    return {origin.x + x, origin.y + y};
}

sf::Vector2f getRectCorner(sf::Vector2f center, sf::Vector2f offset, float rotation)
{
    float theta = rotation * (3.1415926535f / 180.f);

    sf::Vector2f point;

    point.x = center.x + offset.x * std::cos(theta) - offset.y * std::sin(theta);
    point.y = center.y + offset.x * std::sin(theta) + offset.y * std::cos(theta);

    return point;
}

sf::FloatRect getRectBoundingBox(CellManager* cellManager, sf::Vector2f center, sf::Vector2f size, float rotation, bool asGridCoords)
{
    sf::Vector2f tl = getRectCorner(center, {-size.x / 2, -size.y / 2}, rotation);
    sf::Vector2f tr = getRectCorner(center, {size.x / 2, -size.y / 2}, rotation);
    sf::Vector2f bl = getRectCorner(center, {-size.x / 2, size.y / 2}, rotation);
    sf::Vector2f br = getRectCorner(center, {size.x / 2, size.y / 2}, rotation);

    sf::FloatRect boundingBox;

    boundingBox.position.x = std::min({tl.x, tr.x, bl.x, br.x});
    boundingBox.position.y = std::min({tl.y, tr.y, bl.y, br.y});

    float xMax = std::max({tl.x, tr.x, bl.x, br.x});
    float yMax = std::max({tl.y, tr.y, bl.y, br.y});

    boundingBox.size.x = xMax - boundingBox.position.x;
    boundingBox.size.y = yMax - boundingBox.position.y;

    if (asGridCoords)
    {
        boundingBox.position.x -= cellManager->cellOffset.x;
        boundingBox.position.y -= cellManager->cellOffset.y;

        boundingBox.position.x /= cellManager->cellSize;
        boundingBox.position.y /= cellManager->cellSize;

        boundingBox.size.x /= cellManager->cellSize;
        boundingBox.size.y /= cellManager->cellSize;
    }

    return boundingBox;
}

std::vector<sf::Vector2f> getRectAlignedPoints(CellManager* cellManager, sf::Vector2f center, sf::Vector2f size, float rotation, bool asGridCoords)
{   
    int lengthInCells = std::floor(size.x / cellManager->cellSize);
    int widthInCells = std::floor(size.y / cellManager->cellSize);

    sf::FloatRect bBox = getRectBoundingBox(cellManager, center, {size.x + cellManager->beingRectInflationSize.x, size.y + cellManager->beingRectInflationSize.y}, rotation, true);
    
    int startX, startY, endX, endY;

    startX = std::floor(bBox.position.x);
    startY = std::floor(bBox.position.y);

    endY = std::ceil(bBox.position.y + bBox.size.y - 1);
    endX = std::ceil(bBox.position.x + bBox.size.x - 1);

    std::vector<sf::Vector2f> points;

    for (int y = startY; y <= endY; y++)
    {
        for (int x = startX; x <= endX; x++)
        {
            if (pointRectCollide(gridToWorldCoords(cellManager, sf::Vector2i(x, y), true), center, {size.x + cellManager->beingRectInflationSize.x, size.y + cellManager->beingRectInflationSize.y}, rotation))
            {
                asGridCoords ? points.emplace_back(x, y) : points.emplace_back(x * cellManager->cellSize, y * cellManager->cellSize);
            }
        }
    }

    return points;
}

sf::Vector2f gridToWorldCoords(CellManager* cellManager, sf::Vector2i gridCoord, bool convertCenter)
{
    sf::Vector2f point;

    point.x = gridCoord.x * cellManager->cellSize;
    point.y = gridCoord.y * cellManager->cellSize;

    if (convertCenter)
    {
        point.x += cellManager->cellSize / 2;
        point.y += cellManager->cellSize / 2;
    }

    return point;
}

sf::Vector2f gridToWorldCoords(CellManager* cellManager, sf::Vector2u gridCoord, bool convertCenter)
{
    sf::Vector2f point;

    point.x = gridCoord.x * cellManager->cellSize;
    point.y = gridCoord.y * cellManager->cellSize;

    if (convertCenter)
    {
        point.x += cellManager->cellSize / 2;
        point.y += cellManager->cellSize / 2;
    }

    return point;
}

sf::Vector2u worldToGridCoords(CellManager* cellManager, sf::Vector2f worldCoord)
{
    sf::Vector2u point;

    point.x = worldCoord.x / cellManager->cellSize;
    point.y = worldCoord.y / cellManager->cellSize;

    return point;
}

float getDistance(sf::Vector2i vector)
{
    return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

float getDistance(sf::Vector2f vector)
{
    return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

float getDistance(sf::Vector2f vector1, sf::Vector2f vector2)
{
    return sqrt(pow(vector2.x - vector1.x, 2) + pow(vector2.y - vector1.y, 2));
}

float getDistance(sf::Vector2i vector1, sf::Vector2i vector2)
{
    return sqrt(pow(vector2.x - vector1.x, 2) + pow(vector2.y - vector1.y, 2));
}

float getRotation(sf::Vector2i vector)
{
    float degrees = std::atan2(vector.y, vector.x) * (180.f / 3.1415926535f);

    if (degrees < 0.f) degrees += 360.f;
    degrees = 90.f + degrees;
    if (degrees >= 360.f) degrees -= 360.f;

    return degrees;
}