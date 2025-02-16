#include "ball.hpp"
#include "engine.hpp"

Ball::Ball()
{
}

Ball::Ball(float pos_x_meters, float pos_y_meters, float vel_x_mps, float vel_y_mps, float rad_meters, 
           float mass, Color color, bool ignore_floor)
{
    init(pos_x_meters, pos_y_meters, vel_x_mps, vel_y_mps, rad_meters, mass, color, ignore_floor);
}

Ball::~Ball()
{
}

void Ball::init(float pos_x_meters, float pos_y_meters, float vel_x_mps, float vel_y_mps, float rad_meters, 
                float mass, Color color, bool ignore_floor)
{
    this->pos.x = pos_x_meters;
    this->pos.y = pos_y_meters;
    this->vel.x = vel_x_mps;
    this->vel.y = vel_y_mps;
    this->rad = rad_meters;
    this->mass = mass;                              // NOTE: no idea what is this measurement unit
    this->color = color;

    this->ignore_floor = ignore_floor;
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

    if (!ignore_floor)
    {
        if ((pos.y - rad) <= 0.0f)
        {
            vel.y *= -1.0f;
        }
    }

    if ((pos.x + rad) >= SIM_WIDTH || (pos.x - rad) <= 0)
    {
        vel.x *= -1.0f;
    }
}

void Ball::draw() 
{ 
    DrawCircle(map_meters_to_pixel_x(pos.x), 
               map_meters_to_pixel_y(pos.y), 
               map_meters_to_pixel_x(rad), 
               color);
}
