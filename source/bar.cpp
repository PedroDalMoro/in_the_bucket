#include "bar.hpp"
#include "engine.hpp"

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
    DrawLineEx(map_point_to_pixel(start_point_meters), 
               map_point_to_pixel(end_point_meters),
               map_radius_to_pixel(radius_meters),
               color);

    // por que o raio tem que ser / 2? não entendi isso ainda
    DrawCircleV(map_point_to_pixel(start_point_meters), map_radius_to_pixel(radius_meters / 2.0f), color);
    DrawCircleV(map_point_to_pixel(end_point_meters), map_radius_to_pixel(radius_meters / 2.0f), color);
}
