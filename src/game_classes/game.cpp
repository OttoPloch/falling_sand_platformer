#include "game.hpp"

const WindowPreset WINDOWPRESET1(sf::VideoMode({800, 600}), "game", false, false);
const WindowPreset WINDOWPRESET2(sf::VideoMode::getDesktopMode(), "game", false, false);
const WindowPreset WINDOWPRESET3(sf::VideoMode::getDesktopMode(), "game", true, false);

// Temp
const WindowPreset gridSizedWindowPreset(sf::VideoMode({1000, 1000}), "game", false, false);

// DONE: Being Acceleration Value, Rotational Acceleration, Rotational Velocity
// DONE: Give each Cell a Weight value which HeavyBehavior (probably rename) will use to calculate
// (this /\/\/\ will also have to be done for Cell Velocity \/\/\/ to calculate Acceleration)
// DONE: Cell Velocity
// DONE: Fix SinkBehavior so it accounts for RisingBehavior
// DONE: Change cell weight values to floats for more control of fall speed
// DONE: Remove cells from the vertex array when they are moving visually, create a placeholder square to represent it and interpolate \/\/\/, then put the vertices back in the new spot
// DONE: Interpolate updating being sprites and drawing cells (might need to actually properly draw cells for this)
// DONE: Try to fix the "flickering" issue with cells like water that always move, especially when iterating while paused. Could be as simple as them moving too fast

// TODO: soil, seeds and stems (for the "garden" level? was thinking about how to make this game)
// To finish: 
//   - DONE: add a plantID to each plant cell that is created when the stem cell grows and is the same for the entire plant.
//   - DONE: when the stem cell that is the root of the plant gets unplanted, tell it's neighbors to check their neighbors for the same plantID, and if it is the same then change type to dead stem
//   - DONE: splitting behavior that has a chance for a stem cell to grow in two places and they both can grow on their own, making branches
//   - DONE: buds/flowers as a behavior that has a chance to end the branch and create a flower. Maybe plants should grow on their own without water so cool flowers could generate quickly and it would be like gambling >:) to see how big your flower is
//   - certain flowers could be valuable so one method of getting a lot of money or whatever would be making a farm that grows a lot of plants to try and get valuable buds/flowers (for the garden level)


// To improve what has been done so far with plants:
//   - Try to unify the cell preset and cell settings so that behavior settings get applied to cell settings so they can be modified
//   - In some cases change the input method of a setting from the behavior it correlates to to the cell setting when the cell is created
//   - Balance plant growing so that the two extremes (very little growth, taking up the whole screen) don't happen so much and the middle ground happens more
//   - To do this, probably just increase the chance to stop and make a flower every time the plant splits or something like that that would increase the chance of stopping as the plant grows
//   - Improve the method used to turn stem cells into dead stem cells, one way could be adding the ID of the dead plant to a vector in grid.cpp that would get checked every tick and every stem cell that has that ID would get killed.

// Optimize moving cells, an improvement was made i think with turning it into one draw call, but see if you can improve it more.



// TODO: Push Behavior (could help with fixing being/cell interaction)
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
    createWindowFromPreset(gridSizedWindowPreset, window);
    isFullscreen = false;

    isPaused = false;

    world.create(&window, &states);

    creatorPos = {static_cast<unsigned int>(world.getGridSize().x / 2), static_cast<unsigned int>(world.getGridSize().y - 2)};

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
            ticksToProcess += (dt * 1000) / (1000 / 10.f);
            
            // if there was a big stutter, then this will run continuously until it is caught up
            while (ticksToProcess >= 1.f)
            {
                tick();
                
                std::cout << "FPS: " << FPS << "; frame time: " << dt * 1000.f << '\n';

                ticksToProcess -= 1.f;
            }
        }

        update(dt);

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

    // std::cout << "cells: " << world.getCellCount() << '\n';
}

void Game::update(float dt)
{
    world.update(creatorPos, dt);
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
    window.draw(creatorOutline, states);

    window.display();
}

bool Game::getPaused() { return isPaused; }