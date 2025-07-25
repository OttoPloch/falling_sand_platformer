#include "cell.hpp"

#include "../tools/collision.hpp"
#include "../game_classes/being.hpp"

Cell::Cell() {}

Cell::Cell(CellManager* cellManager, Grid* grid, std::vector<std::shared_ptr<Being>>* beings, std::string type, sf::Vector2u position)
{
    create(cellManager, grid, beings, type, position);
}

void Cell::create(CellManager* cellManager, Grid* grid, std::vector<std::shared_ptr<Being>>* beings, std::string type, sf::Vector2u position)
{
    this->cellManager = cellManager;
    this->grid = grid;
    this->beings = beings;
    this->type = type;
    this->position = position;

    velocity = {0, 0};

    weight = cellManager->presets[type].weight;

    myPreset = cellManager->presets[type];
}

void Cell::tick()
{
    if (myPreset.behaviors.size() > 0)
    {
        for (int i = 0; i < myPreset.behaviors.size(); i++)
        {
            if (myPreset.behaviors[i]->update(cellManager, position))
            {
                break;
            }
        }
    }

    if (velocity != sf::Vector2i({0, 0}))
    {
        if (grid->canMoveDistance(position, velocity))
        {
            grid->moveCell(position, {static_cast<int>(velocity.x), static_cast<int>(velocity.y)});
        }
        else
        {
            sf::Vector2i maxDistance = maxMovableDistance(cellManager, position, velocity);

            grid->moveCell(position, maxDistance);

            if ((velocity.x > 0 && !grid->canMoveDistance(position, {1, 0})) || (velocity.x < 0 && !grid->canMoveDistance(position, {-1, 0}))) velocity.x = 0;
            if ((velocity.y > 0 && !grid->canMoveDistance(position, {0, 1})) || (velocity.y < 0 && !grid->canMoveDistance(position, {0, -1}))) velocity.y = 0;
        }
    }
}

void Cell::update()
{

}

void Cell::changeVelocity(sf::Vector2i amount) { velocity += amount; }

void Cell::setPos(sf::Vector2u newPos) { position = newPos; }

void Cell::changePos(sf::Vector2i distance) { position = {position.x + distance.x, position.y + distance.y}; }

void Cell::changeType(std::string newType)
{
    type = newType;

    weight = cellManager->presets[type].weight;

    myPreset = cellManager->presets[type];
}

void Cell::addStartBehavior(std::shared_ptr<Behavior> newBehavior) { myPreset.behaviors.insert(myPreset.behaviors.begin(), newBehavior); }

void Cell::addEndBehavior(std::shared_ptr<Behavior> newBehavior) { myPreset.behaviors.push_back(newBehavior); }

std::string Cell::getType() { return type; }

sf::Vector2i Cell::getVelocity() { return velocity; }

int Cell::getOptionalSetting(std::string settingName)
{
    if (myPreset.optionalSettings.find(settingName) != myPreset.optionalSettings.end())
    {
        return myPreset.optionalSettings[settingName];
    }

    return -2;
}

int Cell::getWeight() { return weight; }

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