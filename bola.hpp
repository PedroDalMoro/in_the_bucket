#ifndef BOLA_HPP
#define BOLA_HPP

#include "defs.hpp"
#include "raylib.h"
#include <string>

class Bola
{
private:
    Vector2 _pos;
    Vector2 _vel;
    int _rad;
    float _amort;

public:
    Bola(int pos_x, int pos_y, int rad);
    ~Bola();

    void update();
    void draw();
};

#endif  // BOLA_HPP