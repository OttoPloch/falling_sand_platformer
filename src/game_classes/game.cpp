#include "game.hpp"

const WindowPreset WINDOWPRESET1(sf::VideoMode({800, 600}), "game", false, false);
const WindowPreset WINDOWPRESET2(sf::VideoMode::getDesktopMode(), "game", false, false);
const WindowPreset WINDOWPRESET3(sf::VideoMode::getDesktopMode(), "game", true, false);

// DONE: Being Acceleration Value, Rotational Acceleration, Rotational Velocity
// DONE: Give each Cell a Weight value which HeavyBehavior (probably rename) will use to calculate
// (this /\/\/\ will also have to be done for Cell Velocity \/\/\/ to calculate Acceleration)
// DONE: Cell Velocity
// DONE: Fix SinkBehavior so it accounts for RisingBehavior

// TODO: Interpolate updating being sprites and drawing cells (might need to actually properly draw cells for this)
// TODO: BeingManager? This would help for tracking constants like gravity for \/\/\/
// TODO: Being Gravity
// TODO: Struct for Being Settings (disableGravity, disableCollision, etc)
// TODO: Fix Being/Cell Interaction
// TODO: Align Being Draw with Grid for better Coherence with Beings + Cells (Collision funcs could stay the same just use grid aligned coords).
// I really like this idea /\/\/\ but it may take a bit to get splitting up the texture and drawing in aligned spots working.
// Also, beings will have to be smaller than their real size and not show their entire texture, so that the squares showing them don't
// have any black/blank parts when the being is rotated. Still, this idea has a lot of potential to make a very immersive feature.

Game::Game() {}

void Game::start()
{
    createWindowFromPreset(WINDOWPRESET1, window);
    isFullscreen = false;

    isPaused = false;

    world.create(&window);

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
            // formula is: milliseconds since last frame / desired milliseconds per update
            // the last number is the desired ups (20 right now)
            ticksToProcess += (dt * 1000) / (1000 / 20.f);
            
            //std::cout << "FPS: " << FPS << "; frame time: " << dt * 1000.f << '\n';
            
            // if there was a big stutter, then this will run continuously until it is caught up
            while (ticksToProcess >= 1.f)
            {
                tick();

                ticksToProcess -= 1.f;
            }
        }

        update();

        draw();
    }
}

void Game::events()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
        else if (event->is<sf::Event::Resized>())
            window.setView(sf::View(sf::FloatRect(sf::Vector2f({0, 0}), sf::Vector2f(window.getSize()))));
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
                    createWindowFromPreset(WINDOWPRESET1, window);
                    window.setPosition({(int)((sf::VideoMode::getDesktopMode().size.x / 2) - window.getSize().x / 2), (int)((sf::VideoMode::getDesktopMode().size.y / 2) - window.getSize().y / 2)});
                    // window.setSize(WINDOWPRESET1.mode.size);
                    // window.setView(sf::View({static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2)}, {static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)}));
                    // window.setPosition({(int)((sf::VideoMode::getDesktopMode().size.x / 2) - window.getSize().x / 2), (int)((sf::VideoMode::getDesktopMode().size.y / 2) - window.getSize().y / 2)});
                }
            }
            
            // set window to preset 2
            if (code == sf::Keyboard::Key::Num2)
            {
                if (!isFullscreen)
                {
                    createWindowFromPreset(WINDOWPRESET2, window);
                    window.setPosition({(int)((sf::VideoMode::getDesktopMode().size.x / 2) - window.getSize().x / 2), (int)((sf::VideoMode::getDesktopMode().size.y / 2) - window.getSize().y / 2)});
                    // window.setSize(WINDOWPRESET2.mode.size);
                    // window.setView(sf::View({static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2)}, {static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)}));
                    // window.setPosition({(int)((sf::VideoMode::getDesktopMode().size.x / 2) - window.getSize().x / 2), (int)((sf::VideoMode::getDesktopMode().size.y / 2) - window.getSize().y / 2)});
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

            if (code == sf::Keyboard::Key::Tab)
            {
                isPaused = !isPaused;
            }

            if (code == sf::Keyboard::Key::Period && isPaused)
            {
                tick();
            }

            ////////////////////////////////////////////////////////
        }
    }
}

void Game::tick()
{
    world.tick(creatorPos);

    std::cout << "cells: " << world.getCellCount() << '\n';
}

void Game::update()
{
    world.update(creatorPos);
}

void Game::draw()
{
    window.clear(sf::Color(35, 35, 40));

    world.draw();

    // TEMP
    sf::RectangleShape creatorOutline({world.getCellSize(), world.getCellSize()});
    creatorOutline.setFillColor(sf::Color::Transparent);
    creatorOutline.setOutlineColor(sf::Color::Green);
    creatorOutline.setOutlineThickness(2.f);
    creatorOutline.setPosition({creatorPos.x * world.getCellSize(), creatorPos.y * world.getCellSize()});
    window.draw(creatorOutline);

    window.display();
}