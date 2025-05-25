#include "game.hpp"

#include "window_presets.hpp"

const WindowPreset WINDOWPRESET1(sf::VideoMode({800, 600}), "game", false, false);
const WindowPreset WINDOWPRESET2(sf::VideoMode::getDesktopMode(), "game", false, true);
const WindowPreset WINDOWPRESET3(sf::VideoMode::getDesktopMode(), "game", true, false);

Game::Game() {}

void Game::start()
{
    createWindowFromPreset(WINDOWPRESET1, window);
    isFullscreen = false;

    grid.create();

    run();
}

void Game::run()
{
    while (window.isOpen())
    {
        events();

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
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            auto code = keyPressed->code;

            if (code == sf::Keyboard::Key::Escape)
            {
                window.close();
            }
            else if (code == sf::Keyboard::Key::Num1)
            {
                window.setSize(WINDOWPRESET1.mode.size);
                window.setPosition({(int)((sf::VideoMode::getDesktopMode().size.x / 2) - window.getSize().x / 2), (int)((sf::VideoMode::getDesktopMode().size.y / 2) - window.getSize().y / 2)});
            }
            else if (code == sf::Keyboard::Key::Num2)
            {
                window.setSize(WINDOWPRESET2.mode.size);
                window.setPosition({(int)((sf::VideoMode::getDesktopMode().size.x / 2) - window.getSize().x / 2), (int)((sf::VideoMode::getDesktopMode().size.y / 2) - window.getSize().y / 2)});
            }
            else if (code == sf::Keyboard::Key::F11)
            {
                isFullscreen = !isFullscreen;

                if (isFullscreen)
                {
                    createWindowFromPreset(WINDOWPRESET3, window);
                }
                else
                {
                    createWindowFromPreset(WINDOWPRESET1, window);
                    window.setPosition({(int)((sf::VideoMode::getDesktopMode().size.x / 2) - window.getSize().x / 2), (int)((sf::VideoMode::getDesktopMode().size.y / 2) - window.getSize().y / 2)});
                }
            }
        }
    }
}

void Game::update()
{

}

void Game::draw()
{
    window.clear(sf::Color(35, 35, 40));

    window.display();
}