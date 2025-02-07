#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "ball.hpp"
#include "bar.hpp"
#include "vector_2.hpp"
#include "bucket.hpp"

Vec2 get_closest_point_on_segment(Vec2 point, Vec2 seg_point_a, Vec2 seg_point_b);
void handle_ball_collision(Ball& b1, Ball& b2, float coef_resitution);
void handle_bar_collision(Bar bar, Ball& bola);
bool is_ball_inside_bucket(Ball ball, Bucket bucket);

// na verdade to fazendo o contrário
float map_pixel_to_meters_x(int pos_x);
float map_pixel_to_meters_y(int pos_y);

int map_meters_to_pixel_x(float pos_x);
int map_meters_to_pixel_y(float pos_y);

Vector2 map_point_to_pixel(Vec2 point);
float map_radius_to_pixel(float rad);

#endif // ENGINE_HPP