#ifndef BALL_HPP
#define BALL_HPP

#include "raylib.h"
#include "defs.hpp"
#include "vector_2.hpp"

class Ball
{
private:
    bool ignore_first_wall;
    bool ignore_floor;

public:
    Vec2 pos;
    Vec2 vel;
    float rad;
    float mass;
    Color color;
    
    Ball();
    Ball(float pos_x_meters, float pos_y_meters, float vel_x_mps, float vel_y_mps, float rad_meters, 
         float mass, Color color, bool ignore_first_wall = false, bool ignore_floor = false);
    ~Ball();

    void init(float pos_x_meters, float pos_y_meters, float vel_x_mps, float vel_y_mps, float rad_meters, 
              float mass, Color color, bool ignore_first_wall = false, bool ignore_floor = false);
              
    void update();
    void draw();
};

#endif  // BALL_HPP