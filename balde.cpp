#include "balde.hpp"


Balde::Balde(int width, int height, Color color)
{
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

