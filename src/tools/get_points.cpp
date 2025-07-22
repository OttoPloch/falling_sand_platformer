#include "get_points.hpp"

sf::Vector2f getRotatedPoint(sf::Vector2f point, float distance, float rotation)
{
    float theta = rotation * (3.1415926535f / 180.f);

    float rx = point.x + distance * std::sin(theta);
    float ry = point.y - distance * std::cos(theta);

    return {rx, ry};
}

sf::Vector2f getRectTopLeft(sf::Vector2f center, sf::Vector2f size, float rotation)
{
    float theta = rotation * (3.1415926535f / 180.f);

    float dx = size.x / 2.f;
    float dy = size.y / 2.f;
    
    float new_dx = dx * std::cos(theta) - dy * std::sin(theta);
    float new_dy = dx * std::sin(theta) + dy * std::cos(theta);

    return {center.x - new_dx, center.y - new_dy};
}

std::vector<sf::Vector2f> getRectAlignedPoints(int cellSize, sf::Vector2i cellOffset, sf::Vector2f center, sf::Vector2f size, float rotation, bool asGridCoords)
{   
    int lengthInCells = std::floor(size.x / cellSize);
    int widthInCells = std::floor(size.y / cellSize);

    sf::Vector2f tl = getRectTopLeft(center, size, rotation);
    
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
                points.back().x /= cellSize;
                points.back().y /= cellSize;

                points.back().x -= cellOffset.x / cellSize;
                points.back().y -= cellOffset.y / cellSize;
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