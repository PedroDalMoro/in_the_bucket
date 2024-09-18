#ifndef BALDE_HPP
#define BALDE_HPP

#include "defs.hpp"
#include "raylib.h"

class Balde
{
private:
    int _width;
    int _height;
    Color _color;

public:
    Balde(int width, int height, Color color);
    ~Balde();

    void draw(int mouse_x, int mouse_y);
};

#endif  // BALDE_HPP