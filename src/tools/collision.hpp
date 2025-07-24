#pragma once

#include <SFML/Graphics.hpp>

#include "../game_classes/being.hpp"
#include "../managers/cell_manager.hpp"

class Grid;

bool gridLineCollide(sf::Vector2u point, sf::Vector2u linePoint1, sf::Vector2u linePoint2);

bool checkCellsInLine(CellManager* cellManager, sf::Vector2u from, sf::Vector2i distance, sf::Vector2i direction, std::vector<std::shared_ptr<Being>>* beings);

bool pointRectCollide(sf::Vector2f point, sf::Vector2f center, sf::Vector2f size, float rotation);

bool pointBeingCollide(sf::Vector2f point, Being* being, sf::Vector2f inflateSize);