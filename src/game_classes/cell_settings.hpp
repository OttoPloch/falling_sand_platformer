#pragma once

#include <SFML/Graphics.hpp>

class CellSettings
{
public:
    CellSettings();

    void init(float weight, unsigned int plantID);

    float getWeight();

    int getWeightCounterInt();

    float incrementWeightCounter();

    float decrementWeightCounter();

    int getWaterLevel();

    void addToWaterLevel(int amount);

    unsigned int getPlantID();

    void setPlantID(int newID);

    int getAge();

    void addAge();
private:
    float weight;

    // if weight has a decimal, this gets incremented to add more precision
    float weightCounter;

    // for plant-related behaviors
    int waterLevel;

    unsigned int plantID;

    int age;
};