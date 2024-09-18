#ifndef RNG_HPP
#define RNG_HPP

#include "defs.hpp"
#include "raylib.h"
#include <ctime>

class RNG
{
private:

public:
    RNG();
    ~RNG();
    float getNormalized(void);
    int getValue(int min, int max);
};

#endif  // RNG_HPP