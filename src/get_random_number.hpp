#pragma once

#include <random>
#include <time.h>

// answer will be somewhere in the
// range of 0 and maxResult
int getRandomInt(int maxResult);

// answer will be somewhere in the
// range of -maxResult and maxResult
int getRandomBalancedInt(int maxResult);