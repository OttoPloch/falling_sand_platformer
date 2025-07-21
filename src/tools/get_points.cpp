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
