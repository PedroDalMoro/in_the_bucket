#include "balde.hpp"


Balde::Balde(int pos_x, int pos_y, int width, int height, Color color)
{
    _pos_x = pos_x;
    _pos_y = pos_y;
    _width = width;
    _height = height;
    _color = color;
}

Balde::~Balde()
{
}

void Balde::draw(int mouse_x, int mouse_y)
{
    DrawRectangle(mouse_x, mouse_y, _width, _height, _color);
}

