#pragma once

#include <SFML/Graphics.hpp>

class Grid;

bool gridLineCollide(sf::Vector2u point, sf::Vector2u linePoint1, sf::Vector2u linePoint2);

bool checkCellsInLine(sf::Vector2u from, sf::Vector2i distance, sf::Vector2i direction, Grid* grid);

bool pointRectCollide(sf::Vector2f point, sf::Vector2f center, sf::Vector2f size, float rotation);