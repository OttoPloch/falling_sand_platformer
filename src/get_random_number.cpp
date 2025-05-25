#include "get_random_number.hpp"

int getRandomInt(int maxResult)
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, maxResult);
    return dist(rng);
}

int getRandomBalancedInt(int maxResult)
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(-maxResult, maxResult);
    return dist(rng);
}