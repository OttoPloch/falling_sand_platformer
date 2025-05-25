#include "behavior.hpp"

#include "cell.hpp"

Behavior::Behavior(std::string name) : name(name) {}

bool Behavior::update(Grid* grid, sf::Vector2u gridPos) { return true; }

std::string Behavior::getName() { return name; }