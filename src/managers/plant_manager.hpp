#pragma once

#include <map>

struct PlantManager
{
    PlantManager();

    void init();
    
    // associates a plant id with a counter for the amount of times it has split
    std::map<unsigned int, int> splitCounts;

    int maxPlantSplits;
};