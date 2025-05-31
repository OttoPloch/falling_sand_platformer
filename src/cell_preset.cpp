#include "cell_preset.hpp"

CellPreset::CellPreset() {}

CellPreset::CellPreset(sf::Color color, std::vector<std::shared_ptr<Behavior>> behaviors)
{
    this->color = color;
    this->behaviors = behaviors;

    optionalSettings = {
        {"heavy", -1},
        {"flammable", -1}
    };

    for (auto i : optionalSettings)
    {
        for (int j = 0; j < behaviors.size(); j++)
        {
            std::cout << i.first << ", " << i.second << " -- " << behaviors[j]->getName() << ", " << behaviors[j]->getSpecialAttribute() << '\n';

            if (behaviors[j]->getName() == i.first && behaviors[j]->getSpecialAttribute() != i.second)
            {
                optionalSettings[i.first] = behaviors[j]->getSpecialAttribute();

                break;
            }
        }
    }
}