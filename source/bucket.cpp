#include "bucket.hpp"
#include "engine.hpp"

Bucket::Bucket()
{
}

Bucket::Bucket(Vec2 pos, float width, float height, float top_bottom_diff, Color color)
{
    init(pos, width, height, top_bottom_diff, color);
}

Bucket::~Bucket()
{
}

void Bucket::update_bucket_points(float new_x, float new_y)
{
    this->point_top_left.x = new_x;
    this->point_top_left.y = new_y;

    this->point_bottom_left.x = new_x + top_bottom_diff;
    this->point_bottom_left.y = new_y - height;

    this->point_bottom_right.x = new_x + width + top_bottom_diff;
    this->point_bottom_right.y = new_y - height;

    this->point_top_right.x = new_x + width + (2 * top_bottom_diff);
    this->point_top_right.y = new_y;

    bar_left.set_start(point_top_left);
    bar_left.set_end(point_bottom_left);
    bar_left.update();

    bar_bottom.set_start(point_bottom_left);
    bar_bottom.set_end(point_bottom_right);
    bar_bottom.update();

    bar_right.set_start(point_bottom_right);
    bar_right.set_end(point_top_right);
    bar_right.update();
}

void Bucket::init(Vec2 pos, float width, float height, float top_bottom_diff, Color color)
{
    this->width = width;
    this->height = height;
    this->top_bottom_diff = top_bottom_diff;
    this->color = color;

    update_bucket_points(pos.x, pos.y);

    bar_left.init(point_top_left, point_bottom_left, 0.15, GRAY);
    bar_bottom.init(point_bottom_left, point_bottom_right, 0.15, GRAY);
    bar_right.init(point_bottom_right, point_top_right, 0.15, GRAY);
}

void Bucket::update(float mouse_x, float mouse_y)
{
    update_bucket_points(mouse_x, mouse_y);
}

void Bucket::draw()
{
    bar_left.draw();
    bar_bottom.draw();
    bar_right.draw();
}
