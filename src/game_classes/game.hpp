#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../presets/window_preset.hpp"
#include "world.hpp"

class Game
{
public:
    Game();

    void start();

    void run();

    void events();

    void tick();

    void update();

    void draw();
private:
    sf::RenderWindow window;

    sf::Clock dtClock;

    World world;

    bool isPaused;

    bool isFullscreen;

    sf::Vector2u creatorPos;
};