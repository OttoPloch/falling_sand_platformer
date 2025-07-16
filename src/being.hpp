#include <SFML/Graphics.hpp>

class Being
{
public:
    Being();

private:
    sf::Vector2f position;

    sf::Vector2f velocity;
    
    float rotation;
};