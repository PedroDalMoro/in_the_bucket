#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "ball.hpp"
#include "bar.hpp"

void handle_ball_collision(Ball& b1, Ball& b2, float coef_resitution);
void handle_bar_collision(Bar bar, Ball& bola);

#endif // PHYSICS_HPP