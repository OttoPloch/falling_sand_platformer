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

bool checkCellsInLine(sf::Vector2u from, sf::Vector2i distance, sf::Vector2i direction, Grid* grid, std::vector<std::shared_ptr<Being>>* beings, int cellSize, sf::Vector2f cellOffset)
{
    // This is the most verbose logging I have ever written.
    // The error was from not using abs() in the for loop. Negative values would skip it entirely.

    /*
    std::cout << "OK, from is " << from.x << ", " << from.y <<
        ". distance is " << distance.x << ", " << distance.y <<
        ". direction is " << direction.x << ", " << direction.y <<
        ".\n";
    */

    if (abs(distance.y) > 0 && abs(distance.x) > 0)
    {
        /*
        std::cout << "since distance.y (" << distance.y <<
            ") as an absolute value (" << abs(distance.y) <<
            ") is greater than 0, and distance.x ("
            << distance.x << ") as an absolute value (" << abs(distance.x) <<
            ") is also greater than 0, I will be doing a double for loop.\n";
        */
        
        for (int y = 1; y <= abs(distance.y); y++)
        {
            //std::cout << "y is " << y << ". I will keep looping while it is <= distance.y (" << distance.y << "). Each loop I will add one to y.\n";

            for (int x = 1; x <= abs(distance.x); x++)
            {
                //std::cout << "x is " << x << ". I will keep looping while it is <= distance.x (" << distance.x << "). Each loop I will add one to x.\n";

                sf::Vector2u currentCoord({from.x + direction.x * x, from.y + direction.y * y});

                //std::cout << "currentCoord is " << currentCoord.x << ", " << currentCoord.y << ". Calculated as {" << from.x << " + " << direction.x << " * " << x << ", " << from.y << " + " << direction.y << " * " << y << "}\n";

                if (gridLineCollide(currentCoord, from, {from.x + distance.x, from.y + distance.y}))
                {
                    //std::cout << "A line going from " << from.x << ", " << from.y << " to " << from.x + distance.x << ", " << from.y + distance.y << " collided with point " << currentCoord.x << ", " << currentCoord.y << ". Now checking if it is nullptr.\n";

                    if (grid->at(currentCoord) != nullptr)
                    {
                        //std::cout << "It is not, so I am returning true to indicate that there was a collision trying to go from " << from.x << ", " << from.y << " to " << from.x + distance.x << ", " << from.y + distance.y << ".\n";

                        return true;
                    }
                    else
                    {
                        //std::cout << "It was nullptr, so I can now move to the next x coord.\n";
                    }

                    if (beings->size() > 0)
                    {
                        for (int i = 0; i < beings->size(); i++)
                        {
                            if (pointBeingCollide(gridToWorldCoords(cellSize, cellOffset, currentCoord, true), (*beings)[i].get()))
                            {
                                return true;
                            }
                        }
                    }
                }
                else
                {
                    //std::cout << "There was not a collision between a line going from " << from.x << ", " << from.y << " to " << from.x + distance.x << ", " << from.y + distance.y << " and a point at " << currentCoord.x << ", " << currentCoord.y << ". Moving to the next x coord.\n";
                }
            }

            //std::cout << "Finished this row of cells, moving to y = " << y + 1 << ".\n";
        }

        //std::cout << "Finished the double for loop and there was no collision.\n";
    }
    else if (abs(distance.y) > 0)
    {
        for (int y = 1; y <= abs(distance.y); y++)
        {
            sf::Vector2u currentCoord({from.x, from.y + direction.y * y});

            if (gridLineCollide(currentCoord, from, {from.x, from.y + distance.y}))
            {
                if (grid->at(currentCoord) != nullptr)
                {
                    return true;
                }

                if (beings->size() > 0)
                {
                    for (int i = 0; i < beings->size(); i++)
                    {
                        if (pointBeingCollide(gridToWorldCoords(cellSize, cellOffset, currentCoord, true), (*beings)[i].get()))
                        { 
                            return true;
                        }
                    }
                }
            }
        }
    }
    else if (abs(distance.x) > 0)
    {
        for (int x = 1; x <= abs(distance.x); x++)
        {
            sf::Vector2u currentCoord({from.x + direction.x * x, from.y});

            if (gridLineCollide(currentCoord, from, {from.x + distance.x, from.y}))
            {
                if (grid->at(currentCoord) != nullptr)
                {
                    return true;
                }

                if (beings->size() > 0)
                {
                    for (int i = 0; i < beings->size(); i++)
                    {
                        if (pointBeingCollide(gridToWorldCoords(cellSize, cellOffset, currentCoord, true), (*beings)[i].get()))
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    else
    {
        std::cout << "in checkCellsInLine(), a cell attempted to move a distance of 0, 0\n";

        return false;
    }

    return false;
}

bool pointRectCollide(sf::Vector2f point, sf::Vector2f center, sf::Vector2f size, float rotation)
{
    size.x += 5;
    size.y += 5;

    sf::Vector2f alignedPoint = rotateAroundPoint(point, center, -rotation);
    
    sf::Vector2f min({center.x - size.x / 2, center.y - size.y / 2});
    sf::Vector2f max({center.x + size.x / 2, center.y + size.y / 2});

    return (alignedPoint.x >= min.x && alignedPoint.x <= max.x && alignedPoint.y >= min.y && alignedPoint.y <= max.y);
}

bool pointBeingCollide(sf::Vector2f point, Being* being)
{
    sf::Vector2f center(being->getPosition());
    sf::Vector2f size(being->getSize());
    float rotation(being->getRotation());

    return pointRectCollide(point, center, size, rotation);
}