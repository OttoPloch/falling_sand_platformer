#include "cell_preset.hpp"

CellPreset::CellPreset() {}

CellPreset::CellPreset(sf::Color color, int weight, std::vector<std::shared_ptr<Behavior>> behaviors)
{
    this->color = color;
    this->weight = weight;
    this->behaviors = behaviors;
}