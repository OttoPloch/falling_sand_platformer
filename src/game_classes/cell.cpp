#include "cell.hpp"

#include "../tools/collision.hpp"
#include "../game_classes/being.hpp"

Cell::Cell() {}

Cell::Cell(CellManager* cellManager, std::string type, sf::Vector2u position, CellSettings cellSettings)
{
    create(cellManager, type, position, cellSettings);
}

void Cell::create(CellManager* cellManager, std::string type, sf::Vector2u position, CellSettings cellSettings)
{
    this->cellManager = cellManager;

    grid = cellManager->grid;
    beings = cellManager->beings;

    this->type = type;
    this->position = position;
    this->cellSettings = cellSettings;

    velocity = {0, 0};

    myPreset = cellManager->presets[type];
}

std::pair<Cell*, bool> Cell::tick(bool log)
{
    bool hasChanged = false;

    if (myPreset.behaviors.size() > 0)
    {
        for (int i = 0; i < myPreset.behaviors.size(); i++)
        {
            if (myPreset.behaviors[i]->update(cellManager, position))
            {
                hasChanged = true;
                
                break;
            }

            if (log) std::cout << myPreset.behaviors[i]->getName() << " failed\n";
        }
    }

    if (velocity != sf::Vector2i({0, 0}))
    {
        if (log) std::cout << "Velocity is not 0, 0. Specifically it is " << velocity.x << ", " << velocity.y << '\n';

        if (grid->canMoveDistance(position, velocity))
        {
            if (log) std::cout << "can move " << velocity.x << ", " << velocity.y << '\n';

            hasChanged = true;
            
            grid->moveCell(position, {static_cast<int>(velocity.x), static_cast<int>(velocity.y)});
        }
        else
        {
            sf::Vector2i maxDistance = maxMovableDistance(cellManager, position, velocity, log);

            if (log) std::cout << "max distance is " << maxDistance.x << ", " << maxDistance.y << '\n';

            hasChanged = true;

            grid->moveCell(position, maxDistance);

            if ((velocity.x > 0 && !grid->canMoveDistance(position, {1, 0})) || (velocity.x < 0 && !grid->canMoveDistance(position, {-1, 0}))) velocity.x = 0;
            if ((velocity.y > 0 && !grid->canMoveDistance(position, {0, 1})) || (velocity.y < 0 && !grid->canMoveDistance(position, {0, -1}))) velocity.y = 0;
        }
    }

    cellSettings.addAge();

    return std::pair(this, hasChanged);
}

void Cell::changeVelocity(sf::Vector2i amount) { velocity += amount; }

void Cell::setPos(sf::Vector2u newPos) { position = newPos; }

void Cell::changePos(sf::Vector2i distance) { position = {position.x + distance.x, position.y + distance.y}; }

void Cell::changeType(std::string newType)
{
    type = newType;

    cellSettings.init(cellManager->presets[type].weight, 0);

    myPreset = cellManager->presets[type];
}

void Cell::addStartBehavior(std::shared_ptr<Behavior> newBehavior) { myPreset.behaviors.insert(myPreset.behaviors.begin(), newBehavior); }

void Cell::addEndBehavior(std::shared_ptr<Behavior> newBehavior) { myPreset.behaviors.push_back(newBehavior); }

int Cell::removeBehavior(std::string behaviorName)
{
    int returnCode = -1;

    if (myPreset.behaviors.size() > 0)
    {
        for (int i = 0; i < myPreset.behaviors.size(); i++)
        {
            if (myPreset.behaviors[i]->getName() == behaviorName)
            {
                if (returnCode < 0)
                {
                    myPreset.behaviors.erase(myPreset.behaviors.begin() + i);
                }

                returnCode++;
            }
        }
    }

    return returnCode;
}

CellSettings* Cell::getCellSettings() { return &cellSettings; }

sf::Vector2u Cell::getPosition() { return position; }

std::string Cell::getType() { return type; }

sf::Vector2i Cell::getVelocity() { return velocity; }

int Cell::getOptionalSetting(std::string settingName)
{
    if (myPreset.optionalSettings.find(settingName) != myPreset.optionalSettings.end())
    {
        return myPreset.optionalSettings[settingName];
    }

    return -1;
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

bool Cell::canSmooth() { return myPreset.canSmooth; }

std::vector<Cell*> Cell::getNeighbors()
{
    std::vector<Cell*> neighbors;

    bool onLeft = (position.x == 0);
    bool onRight = (position.x == grid->getLength() - 1);
    bool onTop = (position.y == 0);
    bool onBottom = (position.y == grid->getHeight() - 1);

    if (!onLeft && !onTop     && grid->at({position.x - 1, position.y - 1}) != nullptr) { neighbors.emplace_back(grid->at({position.x - 1, position.y - 1})); }
    if (!onTop                && grid->at({position.x, position.y - 1})     != nullptr) { neighbors.emplace_back(grid->at({position.x, position.y - 1}));     }
    if (!onRight && !onTop    && grid->at({position.x + 1, position.y - 1}) != nullptr) { neighbors.emplace_back(grid->at({position.x + 1, position.y - 1})); }
    if (!onLeft               && grid->at({position.x - 1, position.y})     != nullptr) { neighbors.emplace_back(grid->at({position.x - 1, position.y}));     }
    if (!onRight              && grid->at({position.x + 1, position.y})     != nullptr) { neighbors.emplace_back(grid->at({position.x + 1, position.y}));     }
    if (!onLeft && !onBottom  && grid->at({position.x - 1, position.y + 1}) != nullptr) { neighbors.emplace_back(grid->at({position.x - 1, position.y + 1})); }
    if (!onBottom             && grid->at({position.x, position.y + 1})     != nullptr) { neighbors.emplace_back(grid->at({position.x, position.y + 1}));     }
    if (!onRight && !onBottom && grid->at({position.x + 1, position.y + 1}) != nullptr) { neighbors.emplace_back(grid->at({position.x + 1, position.y + 1})); }

    return neighbors;
}

std::vector<Cell*> Cell::getNearbySpaces()
{
    std::vector<Cell*> spaces;

    bool onLeft = (position.x == 0);
    bool onRight = (position.x == grid->getLength() - 1);
    bool onTop = (position.y == 0);
    bool onBottom = (position.y == grid->getHeight() - 1);

    if (!onLeft && !onTop    ) { spaces.emplace_back(grid->at({position.x - 1, position.y - 1})); }
    if (!onTop               ) { spaces.emplace_back(grid->at({position.x, position.y - 1}));     }
    if (!onRight && !onTop   ) { spaces.emplace_back(grid->at({position.x + 1, position.y - 1})); }
    if (!onLeft              ) { spaces.emplace_back(grid->at({position.x - 1, position.y}));     }
    if (!onRight             ) { spaces.emplace_back(grid->at({position.x + 1, position.y}));     }
    if (!onLeft && !onBottom ) { spaces.emplace_back(grid->at({position.x - 1, position.y + 1})); }
    if (!onBottom            ) { spaces.emplace_back(grid->at({position.x, position.y + 1}));     }
    if (!onRight && !onBottom) { spaces.emplace_back(grid->at({position.x + 1, position.y + 1})); }

    return spaces;
}