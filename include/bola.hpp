#ifndef BOLA_HPP
#define BOLA_HPP

#include "raylib.h"
#include <string>

#include "defs.hpp"
#include "vector_2.hpp"

class Bola
{
private:
    int _map_x(float pos_x);
    int _map_y(float pos_y);
    int _map_rad(float rad);

public:
    Vec2 pos;
    Vec2 vel;
    float rad;
    float mass;
    Color cor;
    
    Bola(float pos_x_meters, float pos_y_meters, float vel_x_mps, float vel_y_mps, float rad_meters, Color cor);
    Bola();
    ~Bola();

    void init(float pos_x_meters, float pos_y_meters, float vel_x_mps, float vel_y_mps, float rad_meters, Color color);
    void update();
    void draw();
};

#endif  // BOLA_HPP