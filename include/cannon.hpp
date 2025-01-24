#ifndef CANNON_HPP
#define CANNON_HPP

#include "vector_2.hpp"
#include "raylib.h"
#include "ball.hpp"
#include <vector>

struct cannon_configs_t
{
    Vec2 pos;
    Vec2 direction;
    double time_between_shots_s;
    int ball_limit;
    float min_ball_radius;
    float max_ball_radius;
    Color color;
};

class Cannon
{
private:
    double last_shot_time_s;
    cannon_configs_t *cannon_configs;
    
    Ball generate_random_ball(void);

public:
    Cannon();
    Cannon(cannon_configs_t *cannon_configs);
    ~Cannon();

    void init(cannon_configs_t *cannon_configs);
    void update(void);
};

#endif // CANNON_HPP