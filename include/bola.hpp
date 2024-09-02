#ifndef BOLA_HPP
#define BOLA_HPP

#include "raylib.h"
#include <string>

#include "defs.hpp"
#include "vector_2.hpp"

class Bola
{
private:
    Vec2 _pos;
    Vec2 _vel;
    float _rad;
    Color _cor;

    int _map_x(float pos_x);
    int _map_y(float pos_y);
    int _map_rad(float rad);

public:
    Bola(float pos_x_meters, float pos_y_meters, float vel_x_mps, float vel_y_mps, float rad_meters, Color cor);
    Bola();
    ~Bola();

    void init(float pos_x_meters, float pos_y_meters, float vel_x_mps, float vel_y_mps, float rad_meters, Color cor);
    void update();
    void draw();
};

#endif  // BOLA_HPP