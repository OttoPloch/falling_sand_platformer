#include "cell.hpp"

Cell::Cell() {}

Cell::Cell(CellManager* cellManager, Grid* grid, std::string type, sf::Vector2u position)
{
    create(cellManager, grid, type, position);
}

void Cell::create(CellManager* cellManager, Grid* grid, std::string type, sf::Vector2u position)
{
    this->cellManager = cellManager;
    this->grid = grid;
    this->type = type;
    this->position = position;

    myPreset = cellManager->presets[type];
}

void Cell::update()
{
    for (int i = 0; i < myPreset.behaviors.size(); i++)
    {
        if (myPreset.behaviors[i]->update(grid, position))
        {
            break;
        }
    }
}

void Cell::setPos(sf::Vector2u newPos) { position = newPos; }

void Cell::changePos(sf::Vector2i distance)
{
    position.x += distance.x;
    position.y += distance.y;
}

std::string Cell::getType() { return type; }

int Cell::getWeight() { return myPreset.weight; }

sf::Color Cell::getColor()
{
    return myPreset.color;
}

bool Cell::hasBehavior(std::string behaviorName)
{
    for (int i = 0; i < myPreset.behaviors.size(); i++)
    {
        if (myPreset.behaviors[i]->getName() == behaviorName)
        {
            return true;
        }
    }

    return false;
}