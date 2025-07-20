#pragma once

#include <SFML/Graphics.hpp>

struct WindowPreset
{
    WindowPreset(sf::VideoMode mode, std::string title, bool fullscreen, bool borderless);

    sf::VideoMode mode;
    std::string title;
    bool fullscreen;
    bool borderless;
};

sf::RenderWindow& createWindowFromPreset(WindowPreset thePreset, sf::RenderWindow& theWindow);