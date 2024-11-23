#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "bola.hpp"
#include "bar.hpp"

void handle_ball_collision(Bola& b1, Bola& b2, float coef_resitution);
void handle_bar_collision(Bar bar, Bola& bola);


#endif // PHYSICS_HPP