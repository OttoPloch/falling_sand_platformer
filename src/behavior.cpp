#include "behavior.hpp"

#include "cell.hpp"

Behavior::Behavior(std::string name, int specialAttribute) : name(name), specialAttribute(specialAttribute) {}

bool Behavior::update(Grid* grid, sf::Vector2u gridPos) { return true; }

std::string Behavior::getName() { return name; }

int Behavior::getSpecialAttribute() { return specialAttribute; }