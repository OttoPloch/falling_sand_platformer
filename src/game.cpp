#include "game.hpp"

const WindowPreset WINDOWPRESET1(sf::VideoMode({800, 600}), "game", false, false);
const WindowPreset WINDOWPRESET2(sf::VideoMode::getDesktopMode(), "game", false, true);
const WindowPreset WINDOWPRESET3(sf::VideoMode::getDesktopMode(), "game", true, false);

const int GRIDLENGTH = 30;
const int GRIDHEIGHT = 30;

Game::Game() {}

void Game::start()
{
    createWindowFromPreset(WINDOWPRESET1, window);
    window.setFramerateLimit(60);
    isFullscreen = false;

    world.create(GRIDLENGTH, GRIDHEIGHT, &window);

    run();
}

void Game::run()
{
    float ticksToProcess = 0.f;

    while (window.isOpen())
    {
        // gets delta time
        float dt = dtClock.restart().asSeconds();

        // input, window resizing and more
        events();

        float FPS = 1.f / dt;

        if (!isPaused)
        {
            // formula is: milliseconds since last frame / desired millisecondsper update
            // the last number is the desired ups (20 right now)
            ticksToProcess += (dt * 1000) / (1000 / 20.f);

            // if there was a big stutter, then this will run continuously until it is caught up
            while (ticksToProcess >= 1.f)
            {
                update();

                ticksToProcess -= 1.f;
            }
        }

        draw();
    }
}

void Game::events()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            //////////////////// KEYBOARD INPUT ////////////////////
            
            auto code = keyPressed->code;

            // close window
            if (code == sf::Keyboard::Key::Escape)
            {
                window.close();
            }

            // set window to preset 1
            if (code == sf::Keyboard::Key::Num1)
            {
                if (!isFullscreen)
                {
                    window.setSize(WINDOWPRESET1.mode.size);
                    window.setView(sf::View({static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2)}, {static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)}));
                    window.setPosition({(int)((sf::VideoMode::getDesktopMode().size.x / 2) - window.getSize().x / 2), (int)((sf::VideoMode::getDesktopMode().size.y / 2) - window.getSize().y / 2)});
                }
            }
            
            // set window to preset 2
            if (code == sf::Keyboard::Key::Num2)
            {
                if (!isFullscreen)
                {
                    window.setSize(WINDOWPRESET2.mode.size);
                    window.setView(sf::View({static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2)}, {static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)}));
                    window.setPosition({(int)((sf::VideoMode::getDesktopMode().size.x / 2) - window.getSize().x / 2), (int)((sf::VideoMode::getDesktopMode().size.y / 2) - window.getSize().y / 2)});
                }
            }

            // toggles fullscreen
            if (code == sf::Keyboard::Key::F11)
            {
                isFullscreen = !isFullscreen;

                if (isFullscreen)
                {
                    createWindowFromPreset(WINDOWPRESET3, window);
                }
                else
                {
                    // creates window and centers on display
                    createWindowFromPreset(WINDOWPRESET1, window);
                    window.setPosition({(int)((sf::VideoMode::getDesktopMode().size.x / 2) - window.getSize().x / 2), (int)((sf::VideoMode::getDesktopMode().size.y / 2) - window.getSize().y / 2)});
                }
            }
            
            // creates a sand particle; temporary for testing
            if (code == sf::Keyboard::Key::S)
            {
                world.makeACell("sand", {static_cast<unsigned int>(world.getGridSize().x / 2), 1});
            }

            // creates a water particle; temporary for testing
            if (code == sf::Keyboard::Key::W)
            {
                world.makeACell("water", {static_cast<unsigned int>(world.getGridSize().x / 2), 1});
            }

            // creates a fire particle; temporary for testing
            if (code == sf::Keyboard::Key::F)
            {
                world.makeACell("fire", {static_cast<unsigned int>(world.getGridSize().x / 2), 1});
            }

            // creates a wood particle; temporary for testing
            if (code == sf::Keyboard::Key::D)
            {
                world.makeACell("wood", {static_cast<unsigned int>(getRandomInt(GRIDLENGTH - 1)), static_cast<unsigned int>(getRandomInt(GRIDHEIGHT - 1))});
            }

            // creates a smoke particle; temporary for testing
            if (code == sf::Keyboard::Key::O)
            {
                world.makeACell("smoke", {static_cast<unsigned int>(getRandomInt(GRIDLENGTH - 1)), 9});
            }

            ////////////////////////////////////////////////////////
        }
    }
}

void Game::update()
{
    world.update();

    std::cout << "cells: " << world.getCellCount() << '\n';
}

void Game::draw()
{
    window.clear(sf::Color(35, 35, 40));

    world.draw();

    window.display();
}