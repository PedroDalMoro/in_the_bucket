#include "bar.hpp"

Bar::Bar()
{

}

Bar::Bar(Vec2 start_point_meters, Vec2 end_point_meters, float radius_meters, Color color)
{
    init(start_point_meters, end_point_meters, radius_meters, color);
}

Bar::~Bar()
{

}

Vector2 Bar::_map_point(Vec2 point)
{
    Vector2 ret;

    ret.x = static_cast<int>(point.x * SIM_SCALE);
    ret.y = static_cast<int>(SCREEN_HEIGHT - (point.y * SIM_SCALE));

    return ret;
}

float Bar::_map_rad(float rad)
{
    return (rad * SIM_SCALE);
}

void Bar::init(Vec2 start_point_meters, Vec2 end_point_meters, float radius_meters, Color color)
{
    this->start_point_meters = start_point_meters;
    this->end_point_meters = end_point_meters;
    this->radius_meters = radius_meters;
    this->color = color; 
}

void Bar::set_start(Vec2 start_point_meters)
{
    this->start_point_meters = start_point_meters;
}

void Bar::set_end(Vec2 end_point_meters)
{
    this->end_point_meters = end_point_meters;
}
    
void Bar::draw(void)
{
    DrawLineEx(_map_point(start_point_meters), 
               _map_point(end_point_meters),
               _map_rad(radius_meters),
               color);

    // por que o raio tem que ser / 2? não entendi isso ainda
    DrawCircleV(_map_point(start_point_meters), _map_rad(radius_meters / 2.0f), color);
    DrawCircleV(_map_point(end_point_meters), _map_rad(radius_meters / 2.0f), color);
}
