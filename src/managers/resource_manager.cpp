#include "resource_manager.hpp"

#include <iostream>

ResourceManager::ResourceManager() {}

void ResourceManager::load()
{
    path = "../../assets";

    moonPath = "images/moon.jpg";
    sunPath = "images/sun.jpg";
    
    if (!moonTexture.loadFromFile(path / moonPath)) { std::cerr << "Error loading file " << path / moonPath; }
    if (!sunTexture.loadFromFile(path / sunPath)) { std::cerr << "Error loading file " << path / sunPath; }

    textures = 
    {
        {"moon", moonTexture},
        {"sun", sunTexture}
    };
}

sf::Texture* ResourceManager::getTexture(std::string textureName)
{
    if (textures.count(textureName))
    {
        return &textures[textureName];
    }
    else
    {
        return nullptr;
    }
}