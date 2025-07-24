#include "get_points.hpp"

#include <cmath>
#include <iostream>
#include <algorithm>

#include "collision.hpp"

sf::Vector2f getRotatedPoint(sf::Vector2f point, float distance, float rotation)
{
    float theta = rotation * (M_PI / 180.f);

    float rx = point.x + distance * std::sin(theta);
    float ry = point.y - distance * std::cos(theta);

    return {rx, ry};
}

sf::Vector2f rotateAroundPoint(sf::Vector2f point, sf::Vector2f origin, float rotation)
{
    float theta = rotation * (M_PI / 180.f);

    sf::Vector2f translated;

    translated.x = point.x - origin.x;
    translated.y = point.y - origin.y;

    float x = translated.x * std::cos(theta) - translated.y * std::sin(theta);
    float y = translated.x * std::sin(theta) + translated.y * std::cos(theta);

    return {origin.x + x, origin.y + y};
}

sf::Vector2f getRectCorner(sf::Vector2f center, sf::Vector2f offset, float rotation)
{
    float theta = rotation * (M_PI / 180.f);

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
            if (pointRectCollide(gridToWorldCoords(cellManager, {x, y}, true), center, {size.x + cellManager->beingRectInflationSize.x, size.y + cellManager->beingRectInflationSize.y}, rotation))
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

    point.x = cellManager->cellOffset.x + gridCoord.x * cellManager->cellSize;
    point.y = cellManager->cellOffset.y + gridCoord.y * cellManager->cellSize;

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

    point.x = (worldCoord.x - cellManager->cellOffset.x) / cellManager->cellSize;
    point.y = (worldCoord.y - cellManager->cellOffset.y) / cellManager->cellSize;

    return point;
}