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

    void update(float dt);

    void draw();

    bool getPaused();
private:
    sf::RenderWindow window;

    sf::RenderStates states;

    sf::Clock dtClock;

    World world;

    bool isPaused;

    bool isFullscreen;

    sf::Vector2u creatorPos;
};