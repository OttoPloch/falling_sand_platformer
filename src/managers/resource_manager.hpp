#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <unordered_map>

class ResourceManager
{
public:
    ResourceManager();

    void load();

    sf::Texture* getTexture(std::string textureName);
private:
    std::filesystem::path path;

    std::unordered_map<std::string, sf::Texture> textures;

    std::filesystem::path moonPath;
    sf::Texture moonTexture;

    std::filesystem::path sunPath;
    sf::Texture sunTexture;
};