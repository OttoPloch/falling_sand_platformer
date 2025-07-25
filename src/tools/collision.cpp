#include "collision.hpp"

#include <iostream>
#include <math.h>

#include "../game_classes/grid.hpp"
#include "get_points.hpp"

bool gridLineCollide(sf::Vector2u point, sf::Vector2u linePoint1, sf::Vector2u linePoint2)
{
    int dxc = point.x - linePoint1.x;
    int dyc = point.y - linePoint1.y;

    int dxl = linePoint2.x - linePoint1.x;
    int dyl = linePoint2.y - linePoint1.y;

    int cross = dxc * dyl - dyc * dxl;

    if (cross != 0) return false;

    if (abs(dxl) >= abs(dyl))
    {
        if (dxl > 0)
        {
            return linePoint1.x <= point.x && point.x <= linePoint2.x;
        }
        else
        {
            return linePoint2.x <= point.x && point.x <= linePoint1.x;
        }
    }
    else
    {
        if (dyl > 0)
        {
            return linePoint1.y <= point.y && point.y <= linePoint2.y;
        }
        else
        {
            return linePoint2.y <= point.y && point.y <= linePoint1.y;
        }
    }
}

bool checkCellsInLine(CellManager* cellManager, sf::Vector2u from, sf::Vector2i distance)
{
    sf::Vector2i direction;

    (distance.x > 0) ? direction.x = 1 : (distance.x < 0) ? direction.x = -1 : direction.x = 0;
    (distance.y > 0) ? direction.y = 1 : (distance.y < 0) ? direction.y = -1 : direction.y = 0;

    int startX, startY, endX, endY;

    if (abs(distance.x) > 0)
    {
        startX = 1;
        endX = abs(distance.x);
    }
    else
    {
        startX = 0;
        endX = 0;
    }

    if (abs(distance.y) > 0)
    {
        startY = 1;
        endY = abs(distance.y);
    }
    else
    {
        startY = 0;
        endY = 0;
    }

    // Not sure what I should do here, I'll leave this for now
    // until I enter a scenario where I need to resolve it.
    if (distance.x == 0 && distance.y == 0)
    {
        std::cout << "in checkCellsInLine(), a cell attempted to move a distance of 0, 0\n";
        assert(false);

        return false;
    }

    // Iterates through the bounding box of the line that the cell wants to go in
    for (int y = startY; y <= endY; y++)
    {
        for (int x = startX; x <= endX; x++)
        {
            // The current position that will be checked to see if
            // it is in the line that the cell wants to go in.
            sf::Vector2u currentCoord({from.x + direction.x * x, from.y + direction.y * y});

            // This just means currentCoord has the potential to be in
            // the way, it could still be a valid spot to move to.
            if (gridLineCollide(currentCoord, from, {from.x + distance.x, from.y + distance.y}))
            {
                // Cell collision
                if (cellManager->grid->at(currentCoord) != nullptr)
                {
                    return true;
                }

                // Being collision
                if (cellManager->beings->size() > 0)
                {
                    for (int i = 0; i < cellManager->beings->size(); i++)
                    {
                        if (pointBeingCollide(gridToWorldCoords(cellManager, {static_cast<int>(currentCoord.x), static_cast<int>(currentCoord.y)}, true), (*cellManager->beings)[i].get(), cellManager->beingRectInflationSize))
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    
    return false;
}

bool pointRectCollide(sf::Vector2f point, sf::Vector2f center, sf::Vector2f size, float rotation)
{
    sf::Vector2f alignedPoint = rotateAroundPoint(point, center, -rotation);
    
    sf::Vector2f min({center.x - size.x / 2, center.y - size.y / 2});
    sf::Vector2f max({center.x + size.x / 2, center.y + size.y / 2});

    return (alignedPoint.x >= min.x && alignedPoint.x <= max.x && alignedPoint.y >= min.y && alignedPoint.y <= max.y);
}

bool pointBeingCollide(sf::Vector2f point, Being* being, sf::Vector2f inflateSize = {0, 0})
{
    sf::Vector2f center(being->getPosition());
    sf::Vector2f size(being->getSize());
    float rotation(being->getRotation());

    if (inflateSize != sf::Vector2f({0, 0}))
    {
        size.x += inflateSize.x;
        size.y += inflateSize.y;
    }

    return pointRectCollide(point, center, size, rotation);
}

sf::Vector2i maxMovableDistance(CellManager* cellManager, sf::Vector2u from, sf::Vector2i distance)
{
    if (cellManager->grid->canMoveDistance(from, distance))
    {
        return distance;
    }
    else
    {
        float vectorRotation = getRotation(distance);

        float distanceLength = getDistance(distance) - 1.f;

        sf::Vector2f modifiedDistance = getRotatedPoint({0, 0}, distanceLength, vectorRotation);

        if (modifiedDistance == sf::Vector2f({0, 0})) return {0, 0};

        while (checkCellsInLine(cellManager, from, {static_cast<int>(modifiedDistance.x), static_cast<int>(modifiedDistance.y)}) || from.x + modifiedDistance.x < 0 || from.x + modifiedDistance.x > cellManager->grid->getSizeOfRow(from.x) - 1 || from.y + modifiedDistance.y < 0 || from.y + modifiedDistance.y > cellManager->grid->getSize() - 1)
        {
            distanceLength -= 1.f;

            modifiedDistance = getRotatedPoint({0, 0}, distanceLength, vectorRotation);

            if (modifiedDistance == sf::Vector2f({0, 0})) return {0, 0};
        }

        return {static_cast<int>(modifiedDistance.x), static_cast<int>(modifiedDistance.y)};
    }
}