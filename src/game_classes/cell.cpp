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
    if (myPreset.behaviors.size() > 0)
    {
        for (int i = 0; i < myPreset.behaviors.size(); i++)
        {
            if (myPreset.behaviors[i]->update(grid, position))
            {
                break;
            }
        }
    }
}

void Cell::setPos(sf::Vector2u newPos) { position = newPos; }

void Cell::changePos(sf::Vector2i distance)
{
    position.x += distance.x;
    position.y += distance.y;
}

void Cell::changeType(std::string newType)
{
    type = newType;

    myPreset = cellManager->presets[type];
}

void Cell::addStartBehavior(std::shared_ptr<Behavior> newBehavior)
{
    myPreset.behaviors.insert(myPreset.behaviors.begin(), newBehavior);
}

void Cell::addEndBehavior(std::shared_ptr<Behavior> newBehavior)
{
    myPreset.behaviors.push_back(newBehavior);
}

std::string Cell::getType() { return type; }

int Cell::getOptionalSetting(std::string settingName)
{
    if (myPreset.optionalSettings.find(settingName) != myPreset.optionalSettings.end())
    {
        return myPreset.optionalSettings[settingName];
    }

    return -2;
}

sf::Color Cell::getColor() { return myPreset.color; }

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