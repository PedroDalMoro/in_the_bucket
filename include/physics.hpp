#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "ball.hpp"
#include "bar.hpp"

void handle_ball_collision(Ball& b1, Ball& b2, float coef_resitution);
void handle_bar_collision(Bar bar, Ball& bola);

// na verdade to fazendo o contrário
float map_pixel_to_meters_x(int pos_x);
float map_pixel_to_meters_y(int pos_y);

int map_meters_to_pixel_x(float pos_x);
int map_meters_to_pixel_y(float pos_y);

#endif // PHYSICS_HPP