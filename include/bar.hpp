#ifndef BAR_HPP
#define BAR_HPP

#include "defs.hpp"
#include "raylib.h"
#include "vector_2.hpp"

class Bar
{
private:
    Vector2 _map_point(Vec2 point);
    float _map_rad(float rad);

public:
    Vec2 start_point_meters;
    Vec2 end_point_meters;
    float radius_meters;
    Color color;

    Bar();
    Bar(Vec2 start_point_meters, Vec2 end_point_meters, float radius_meters, Color color);
    ~Bar();

    void init(Vec2 start_point_meters, Vec2 end_point_meters, float radius_meters, Color color);
    void set_start(Vec2 start_point_meters);
    void set_end(Vec2 end_point_meters);
    void draw(void);
};

#endif  // BAR_HPP