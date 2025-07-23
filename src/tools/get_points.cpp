#include "get_points.hpp"

#include <cmath>
#include <iostream>
#include <algorithm>

sf::Vector2f getRotatedPoint(sf::Vector2f point, float distance, float rotation)
{
    float theta = rotation * (M_PI / 180.f);

    float rx = point.x + distance * std::sin(theta);
    float ry = point.y - distance * std::cos(theta);

    return {rx, ry};
}

sf::Vector2f rotateAroundPoint(sf::Vector2f point, sf::Vector2f origin, float rotationAmount)
{
    float theta = rotationAmount * (M_PI / 180.f);

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

sf::FloatRect getRectBoundingBox(int cellSize, sf::Vector2f cellOffset, sf::Vector2f center, sf::Vector2f size, float rotation, bool asGridCoords)
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
        boundingBox.position.x -= cellOffset.x;
        boundingBox.position.y -= cellOffset.y;

        boundingBox.position.x /= cellSize;
        boundingBox.position.y /= cellSize;

        boundingBox.size.x /= cellSize;
        boundingBox.size.y /= cellSize;
    }

    return boundingBox;
}

std::vector<sf::Vector2f> getRectAlignedPoints(int cellSize, sf::Vector2f cellOffset, sf::Vector2f center, sf::Vector2f size, float rotation, bool asGridCoords)
{   
    int lengthInCells = std::floor(size.x / cellSize);
    int widthInCells = std::floor(size.y / cellSize);

    sf::Vector2f tl = getRectCorner(center, {-size.x / 2, -size.y / 2}, rotation);
    
    // This offsets all the points by a bit
    //tl = getRotatedPoint(tl, sqrt(2) * cellSize, -45 + rotation);

    // Puts all the points in the center instead of the top left.
    // Writing this line a while after the one above, turns out
    // this really helps in odd cases like movement + rotation,
    // since a point will round to the next spot at a different time
    // due to the unrounded coord being in the middle rather than corner.
    // This helps the points be more aligned with the center and not stick
    // out on a few sides.
    tl = getRotatedPoint(tl, sqrt(2) * cellSize / 2, 135 + rotation);
    
    sf::Vector2f lastPoint = tl;
    sf::Vector2f firstOfLastColumn = tl;



    std::vector<sf::Vector2f> points;
    std::vector<sf::Vector2f> finalPoints;
    
    for (int y = 0; y < widthInCells; y++)
    {
        for (int x = 0; x < lengthInCells; x++)
        {
            if (x == 0)
            {
                if (y == 0)
                {
                    points.emplace_back(tl);
                }
                else
                {
                    points.emplace_back(getRotatedPoint(firstOfLastColumn, cellSize, 180 + rotation));

                    lastPoint = points.back();
                }

                firstOfLastColumn = points.back();
            }
            else
            {
                points.emplace_back(getRotatedPoint(lastPoint, cellSize, 90 + rotation));

                lastPoint = points.back();
            }

            points.back().x -= std::fmod(points.back().x, cellSize);
            points.back().y -= std::fmod(points.back().y, cellSize);

            if (asGridCoords)
            {
                points.back().x -= cellOffset.x;
                points.back().y -= cellOffset.y;
                
                points.back().x /= cellSize;
                points.back().y /= cellSize;
            }

            auto uniquePoint = std::find(points.begin(), points.end(), points.back());

            if (uniquePoint != points.end())
            {
                if (uniquePoint == points.begin() + points.size() - 1) finalPoints.push_back(points.back());
            }
        }
    }

    return finalPoints;
}

sf::Vector2f gridToWorldCoords(int cellSize, sf::Vector2f cellOffset, sf::Vector2u gridCoord, bool convertCenter)
{
    sf::Vector2f point;

    point.x = cellOffset.x + gridCoord.x * cellSize;
    point.y = cellOffset.y + gridCoord.y * cellSize;

    if (convertCenter)
    {
        point.x += cellSize / 2;
        point.y += cellSize / 2;
    }

    return point;
}

sf::Vector2u worldToGridCoords(int cellSize, sf::Vector2f cellOffset, sf::Vector2f worldCoord)
{
    sf::Vector2u point;

    point.x = (worldCoord.x - cellOffset.x) / cellSize;
    point.y = (worldCoord.y - cellOffset.y) / cellSize;

    return point;
}