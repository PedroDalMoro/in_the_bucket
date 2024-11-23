#include "bucket.hpp"


Bucket::Bucket(int width, int height, Color color)
{
    this->width = width;
    this->height = height;
    this->color = color;
}

Bucket::~Bucket()
{
}

void Bucket::draw(int mouse_x, int mouse_y)
{
    DrawRectangle(mouse_x, mouse_y, width, height, color);
}

