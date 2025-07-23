#include "window_preset.hpp"

WindowPreset::WindowPreset(sf::VideoMode mode, std::string title, bool fullscreen, bool borderless)
{
    this->mode = mode;
    this->title = title;
    this->fullscreen = fullscreen;
    this->borderless = borderless;
}

sf::RenderWindow& createWindowFromPreset(WindowPreset thePreset, sf::RenderWindow& theWindow)
{
    if (thePreset.borderless)
    {
        theWindow.create(thePreset.mode, thePreset.title, sf::Style::None);    
    }
    else
    {
        if (!thePreset.fullscreen)
        {
            theWindow.create(thePreset.mode, thePreset.title, sf::Style::Close);    
        }
        else
        {
            theWindow.create(thePreset.mode, thePreset.title, sf::State::Fullscreen);
        }
    }

    //theWindow.setFramerateLimit(60);

    return theWindow;
}