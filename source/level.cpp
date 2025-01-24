#include "level.hpp"

#include "rng.hpp"
#include "engine.hpp"

std::vector<Ball> Level::balls;

Level::Level(const level_configs_t level_configs, user_input_t *user_input)
{
    this->user_input = user_input;
    this->configs = level_configs;

    setup();
}

Level::~Level() 
{

}

void Level::setup(void) 
{ 
    balls.clear();
    bucket.init(Vec2(0.0f, 0.0f), 2.0f, 3.0f, 1.0f, RED);

    cannon_configs.pos = Vec2(SIM_WIDTH_IN_METERS - 1.0f, 12.0f),
    cannon_configs.direction = Vec2(-15.0f, 0.0f),
    cannon_configs.time_between_shots_s = 0.377f,
    cannon_configs.ball_limit = 30,
    cannon_configs.min_ball_radius = 0.25f,
    cannon_configs.max_ball_radius = 0.40f,
    cannon_configs.color = BLUE;
    cannon.init(&cannon_configs);

    cannon2_configs.pos = Vec2(1.0f, 12.0f),
    cannon2_configs.direction = Vec2(15.0f, 0.0f),
    cannon2_configs.time_between_shots_s = 0.236f,
    cannon2_configs.ball_limit = 30,
    cannon2_configs.min_ball_radius = 0.25f,
    cannon2_configs.max_ball_radius = 0.40f,
    cannon2_configs.color = WHITE;
    cannon2.init(&cannon2_configs);
}

void Level::register_new_ball(Ball ball)
{
    balls.push_back(ball);
}

void Level::loop()
{
    cannon.update();
    cannon2.update();
    bucket.update(user_input->position_on_x_axis, user_input->position_on_y_axis);

    for (size_t i = 0; i < balls.size(); i++)
    {
        balls[i].update();

        for (size_t j = i + 1; j < balls.size(); j++)
        {
            handle_ball_collision(balls[i], balls[j], 0.707f);
        }

        handle_bar_collision(bucket.bar_left, balls[i]);
        handle_bar_collision(bucket.bar_bottom, balls[i]);
        handle_bar_collision(bucket.bar_right, balls[i]);
        balls[i].draw();

        if ((balls[i].pos.y - balls[i].rad) <= 0.0f)
        {
            balls.erase(balls.begin() + i);
        }
    }

    bucket.draw();
}
