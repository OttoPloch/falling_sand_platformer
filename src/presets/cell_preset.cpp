#include "cell_preset.hpp"

CellPreset::CellPreset() {}

CellPreset::CellPreset(float weight, bool canSmooth, sf::Color color, std::vector<std::shared_ptr<Behavior>> behaviors)
{
    this->weight = weight;
    this->canSmooth = canSmooth;
    this->color = color;
    this->behaviors = behaviors;

    optionalSettings = {
        {"flammable", -1},
        {"burning", -1},
        {"flow", -1},
        {"seed", -1},
        {"grow", -1}
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