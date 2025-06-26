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

    creatorPos = {static_cast<unsigned int>(world.getGridSize().x / 2), 1};

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
                world.makeACell("sand", creatorPos);
            }

            // creates a water particle; temporary for testing
            if (code == sf::Keyboard::Key::W)
            {
                world.makeACell("water", creatorPos);
            }

            // creates a fire particle; temporary for testing
            if (code == sf::Keyboard::Key::F)
            {
                world.makeACell("fire", creatorPos);
            }

            // creates a wood particle; temporary for testing
            if (code == sf::Keyboard::Key::D)
            {
                world.makeACell("wood", creatorPos);
            }

            // creates a smoke particle; temporary for testing
            if (code == sf::Keyboard::Key::O)
            {
                world.makeACell("smoke", creatorPos);
            }

            // delete a cell
            if (code == sf::Keyboard::Key::X)
            {
                world.deleteACell(creatorPos);
            }

            // moves the creator position left
            if (code == sf::Keyboard::Key::Left && creatorPos.x > 0)
            {
                creatorPos.x--;
            }

            // moves the creator position right
            if (code == sf::Keyboard::Key::Right && creatorPos.x < world.getGridSize().x - 1)
            {
                creatorPos.x++;
            }

            // moves the creator position up
            if (code == sf::Keyboard::Key::Up && creatorPos.y > 0)
            {
                creatorPos.y--;
            }

            // moves the creator position down
            if (code == sf::Keyboard::Key::Down && creatorPos.y < world.getGridSize().y - 1)
            {
                creatorPos.y++;
            }

            ////////////////////////////////////////////////////////
        }
    }
}

void Game::update()
{
    world.update(creatorPos);

    std::cout << "cells: " << world.getCellCount() << '\n';
}

void Game::draw()
{
    window.clear(sf::Color(35, 35, 40));

    world.draw();

    sf::RectangleShape creatorOutline({static_cast<float>(world.getCellSize().x), static_cast<float>(world.getCellSize().y)});
    creatorOutline.setFillColor(sf::Color::Transparent);
    creatorOutline.setOutlineColor(sf::Color::Green);
    creatorOutline.setOutlineThickness(5.f);
    creatorOutline.setPosition({static_cast<float>(creatorPos.x * world.getCellSize().x), static_cast<float>(creatorPos.y * world.getCellSize().y)});

    window.draw(creatorOutline);

    window.display();
}