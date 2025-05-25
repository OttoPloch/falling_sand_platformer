#pragma once

#include <SFML/Graphics.hpp>

#include "grid.hpp"

class Game
{
public:
    Game();

    void start();

    void run();

    void events();

    void update();

    void draw();
private:
    sf::RenderWindow window;

    sf::Clock dtClock;

    Grid grid;

    bool isPaused;

    bool isFullscreen;
};