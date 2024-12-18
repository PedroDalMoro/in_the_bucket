#ifndef BALL_HPP
#define BALL_HPP

#include "raylib.h"
#include "defs.hpp"
#include "vector_2.hpp"

class Ball
{
private:

public:
    Vec2 pos;
    Vec2 vel;
    float rad;
    float mass;
    Color color;
    
    Ball(float pos_x_meters, float pos_y_meters, float vel_x_mps, float vel_y_mps, float rad_meters, float mass, Color color);
    Ball();
    ~Ball();

    void init(float pos_x_meters, float pos_y_meters, float vel_x_mps, float vel_y_mps, float rad_meters, float mass, Color color);
    void update();
    void draw();
};

#endif  // BALL_HPP