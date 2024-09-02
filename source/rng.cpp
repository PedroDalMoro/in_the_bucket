#include "rng.hpp"

RNG::RNG()
{
    SetRandomSeed(time(NULL));
}

RNG::~RNG()
{
}

float RNG::getNormalized(void)
{
    return (static_cast<float>(GetRandomValue(0, 10000)) / 10000.0f);
}

int RNG::getValue(int min, int max)
{
    return (GetRandomValue(min, max));
}
