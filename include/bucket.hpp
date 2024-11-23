#ifndef BUCKET_HPP
#define BUCKET_HPP

#include "defs.hpp"
#include "raylib.h"

class Bucket
{
private:
    int width;
    int height;
    Color color;

public:
    Bucket(int width, int height, Color color);
    ~Bucket();

    void draw(int mouse_x, int mouse_y);
};

#endif  // BUCKET_HPP