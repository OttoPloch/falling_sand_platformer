#include "cell_preset.hpp"

CellPreset::CellPreset() {}

CellPreset::CellPreset(sf::Color color, std::vector<std::shared_ptr<Behavior>> behaviors)
{
    this->color = color;
    this->behaviors = behaviors;
}