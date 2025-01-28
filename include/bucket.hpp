#ifndef BUCKET_HPP
#define BUCKET_HPP

#include "raylib.h"
#include "defs.hpp"
#include "vector_2.hpp"
#include "bar.hpp"

#define BUCKET_HEIGHT   4

class Bucket
{
private:
    float width;
    float height;
    float top_bottom_diff;
    Color color;

    Vec2 point_top_left;
    Vec2 point_bottom_left;
    Vec2 point_top_right;
    Vec2 point_bottom_right;

    void update_bucket_points(float new_x, float new_y);
    
public:
    Bar bar_left;
    Bar bar_bottom;
    Bar bar_right;
    
    Bucket();
    Bucket(Vec2 pos, float width, float height, float top_bottom_diff, Color color);
    ~Bucket();

    void init(Vec2 pos, float width, float height, float top_bottom_diff, Color color);
    void update(float mouse_x, float mouse_y);
    void draw();
};

#endif  // BUCKET_HPP