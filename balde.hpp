#ifndef BALDE_HPP
#define BALDE_HPP

#include "raylib.h"

class Balde
{
private:
    int _pos_x;
    int _pos_y;
    int _width;
    int _height;
    Color _color;

public:
    Balde(int pos_x, int pos_y, int width, int height, Color color);
    ~Balde();

    void draw(int mouse_x, int mouse_y);
};

#endif  // BALDE_HPP