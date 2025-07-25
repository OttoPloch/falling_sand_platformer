#include "behavior.hpp"

#include "../../game_classes/cell.hpp"

Behavior::Behavior(std::string name, int specialAttribute) : name(name), specialAttribute(specialAttribute) {}

bool Behavior::update(CellManager* cellManager, sf::Vector2u gridPos) { return true; }

std::string Behavior::getName() { return name; }

int Behavior::getSpecialAttribute() { return specialAttribute; }