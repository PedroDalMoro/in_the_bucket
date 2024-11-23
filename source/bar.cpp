#include "bar.hpp"

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

Bar::Bar(Vec2 start_point_meters, Vec2 end_point_meters, float radius_meters, Color color)
{
    this->start_point_meters = start_point_meters;
    this->end_point_meters = end_point_meters;
    this->radius_meters = radius_meters;
    this->color = color; 
}

Bar::~Bar()
{

}

void Bar::draw(void)
{
    DrawLineEx(_map_point(start_point_meters), 
               _map_point(end_point_meters),
               _map_rad(radius_meters),
               color);

    DrawCircleV(_map_point(start_point_meters), _map_rad(radius_meters / 2.0f), color);
    DrawCircleV(_map_point(end_point_meters), _map_rad(radius_meters / 2.0f), color);
}

