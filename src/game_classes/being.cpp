#include "being.hpp"

Being::Being() : position({0.f, 0.f}), velocity({0.f, 0.f}), rotation(0.f) {}

Being::Being(sf::Vector2f position, sf::Vector2f size, float rotation, sf::Texture* myTexture, sf::RenderWindow* window, Grid* grid)
{
    create(position, size, rotation, texture, window, grid);
}

void Being::create(sf::Vector2f position, sf::Vector2f size, float rotation, sf::Texture *texture, sf::RenderWindow* window, Grid* grid)
{
    this->position = position;
    this->size = size;
    this->rotation = rotation;
    this->texture = texture;
    this->window = window;
    this->grid = grid;

    velocity = {1.f, 0.f};

    spriteInit();

    getAlignedPoints();
}

void Being::spriteInit()
{
    sprite = std::make_shared<sf::Sprite>(*texture);
    sprite->setScale({size.x / sprite->getTexture().getSize().x, size.y / sprite->getTexture().getSize().y});
    sprite->setOrigin(sprite->getLocalBounds().getCenter());
    sprite->setPosition(position);
    sprite->setRotation(sf::degrees(rotation));
}

std::vector<std::vector<sf::Vector2f>> Being::getAlignedPoints()
{
    int cellSize = grid->getCellSize();
    
    int lengthInCells = std::floor(size.x / cellSize);
    int widthInCells = std::floor(size.y / cellSize);

    sf::Vector2f tl = getRectTopLeft(position, size, rotation);

    // puts all the points in the center instead of the top left
    //tl = getRotatedPoint(tl, sqrt(2) * cellSize / 2, 135 + rotation);
    
    sf::Vector2f lastPoint = tl;
    sf::Vector2f firstOfLastColumn = tl;



    std::vector<std::vector<sf::Vector2f>> points;
    
    points.resize(widthInCells);
    
    for (int y = 0; y < points.size(); y++)
    {
        points[y].resize(lengthInCells);

        for (int x = 0; x < points[y].size(); x++)
        {
            if (x == 0)
            {
                if (y == 0)
                {
                    points[y][x] = tl;
                }
                else
                {
                    points[y][x] = getRotatedPoint(firstOfLastColumn, cellSize, 180 + rotation);

                    lastPoint = points[y][x];
                }

                firstOfLastColumn = points[y][x];
            }
            else
            {
                points[y][x] = getRotatedPoint(lastPoint, cellSize, 90 + rotation);

                lastPoint = points[y][x];
            }
        }
    }

    return points;
}

float Being::getRotation() { return rotation; }

void Being::rotate(float amount)
{
    rotation += amount;

    if (rotation > 360.f) std::fmod(rotation, 360.f);

    sprite->setRotation(sf::degrees(rotation));
}

void Being::tick()
{
    position.x += velocity.x;
    position.y += velocity.y;
}

void Being::update()
{
    sprite->setPosition(position);
}

void Being::draw()
{
    window->draw(*sprite);
}