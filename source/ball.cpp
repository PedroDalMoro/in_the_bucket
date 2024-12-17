#include "ball.hpp"

int Ball::_map_x(float pos_x)
{
    return (static_cast<int>(pos_x * SIM_SCALE));
}

int Ball::_map_y(float pos_y)
{
    return (static_cast<int>(SCREEN_HEIGHT - (pos_y * SIM_SCALE)));
}

int Ball::_map_rad(float rad)
{
    return (static_cast<int>(rad * SIM_SCALE));
}

Ball::Ball(float pos_x_meters, float pos_y_meters, float vel_x_mps, float vel_y_mps, float rad_meters, float mass, Color cor)
{
    init(pos_x_meters, pos_y_meters, vel_x_mps, vel_y_mps, rad_meters, mass, cor);
}

Ball::Ball()
{
}

Ball::~Ball()
{
}

void Ball::init(float pos_x_meters, float pos_y_meters, float vel_x_mps, float vel_y_mps, float rad_meters, float mass, Color color)
{
    this->pos.x = pos_x_meters;
    this->pos.y = pos_y_meters;
    this->vel.x = vel_x_mps;
    this->vel.y = vel_y_mps;
    this->rad = rad_meters;
    this->mass = mass;            // não faço ideia da unidade que isso vale agora
    this->color = color;
}

void Ball::update()
{
    float dt = GetFrameTime();

    float sdt = dt / 5.0f;
    for (size_t i = 0; i < 5; i++)
    {
        vel.y += -9.81f * sdt;
        pos.y += vel.y * sdt;

        pos.x += vel.x * sdt;
    }

    if((pos.y - rad) <= 0.0f)
    {
        vel.y *= -1.0f;
    }

    if((pos.x + rad) >= SIM_WIDTH || (pos.x - rad) <= 0)
    {
        vel.x *= -1.0f;
    }
}

void Ball::draw()
{
    DrawCircle(_map_x(pos.x), 
                _map_y(pos.y), 
                _map_rad(rad), 
                color);
}
