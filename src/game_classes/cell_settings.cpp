#include "cell_settings.hpp"

CellSettings::CellSettings() {}

void CellSettings::init(float weight, unsigned int plantID)
{
    this->weight = weight;
    this->plantID = plantID;

    weightCounter = 0;

    waterLevel = 0;

    age = 0;
}

float CellSettings::getWeight() { return weight; }

int CellSettings::getWeightCounterInt() { return static_cast<int>(weightCounter); }

float CellSettings::incrementWeightCounter()
{
    weightCounter += weight;

    return weight;
}

float CellSettings::decrementWeightCounter()
{
    float prevCounter = weightCounter;

    weightCounter -= static_cast<int>(weightCounter);

    return prevCounter;
}

int CellSettings::getWaterLevel() { return waterLevel; }

void CellSettings::addToWaterLevel(int amount) { waterLevel += amount; }

unsigned int CellSettings::getPlantID() { return plantID; }

void CellSettings::setPlantID(int newID) { plantID = newID; }

int CellSettings::getAge() { return age; }

void CellSettings::addAge() { age++; }