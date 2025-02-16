#include "cannon.hpp"
#include "rng.hpp"
#include "level.hpp"

Cannon::Cannon() 
{
}

Cannon::Cannon(cannon_configs_t *cannon_configs) 
{ 
    init(cannon_configs); 
}

Cannon::~Cannon() 
{

}

Ball Cannon::generate_random_ball(void)
{
    float radius = RNG::getValue(static_cast<int>(cannon_configs->min_ball_radius * 1000.0f), 
                                 static_cast<int>(cannon_configs->max_ball_radius * 1000.0f));
    radius /= 1000.0f;

    this->cannon_configs->ball_limit--;

    Ball ball(cannon_configs->pos.x, 
              cannon_configs->pos.y, 
              cannon_configs->direction.x + (4.0f * RNG::getNormalized()) - 2.0f,       // -2 to 2 variation 
              cannon_configs->direction.y + (4.0f * RNG::getNormalized()) - 2.0f, 
              radius, 
              PI * radius * radius,
              cannon_configs->color,
              true);

    return ball;
}

void Cannon::init(cannon_configs_t *cannon_configs)
{
    this->cannon_configs = cannon_configs;
    this->last_shot_time_s = 0.0f;
}

void Cannon::update(void)
{
    double time_since_last_shot_s = GetTime() - last_shot_time_s;
    if (time_since_last_shot_s > cannon_configs->time_between_shots_s && 
        this->cannon_configs->ball_limit > 0)
    {
        Level::register_new_ball(generate_random_ball());
        last_shot_time_s = GetTime();
    }
}
