#include "bucket.hpp"
#include "physics.hpp"

Bucket::Bucket(Vec2 pos, float width, float height, float top_bottom_diff, Color color)
{
    this->pos = pos;
    this->width = width;
    this->height = height;
    this->top_bottom_diff = top_bottom_diff;
    this->color = color;

    update_bucket_points(pos.x, pos.y);

    bar1.init(point_top_left, point_bottom_left, 0.15, BLUE);
    bar2.init(point_bottom_left, point_bottom_right, 0.15, YELLOW);
    bar3.init(point_bottom_right, point_top_right, 0.15, RED);
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

    bar1.set_start(point_top_left);
    bar1.set_end(point_bottom_left);
    bar2.set_start(point_bottom_left);
    bar2.set_end(point_bottom_right);
    bar3.set_start(point_bottom_right);
    bar3.set_end(point_top_right);
}

Bucket::~Bucket()
{
}

void Bucket::draw(float mouse_x, float mouse_y)
{
    update_bucket_points(mouse_x, mouse_y);

    bar1.draw();
    bar2.draw();
    bar3.draw();
}

