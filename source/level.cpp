#include "level.hpp"

#include "rng.hpp"
#include "engine.hpp"
#include <string>
#include <iostream>

#define CANNON_STARTING_VECTORS     2                   // [0]: pos, [1]: direction

static Vec2 cannon_starting_positions[][CANNON_STARTING_VECTORS] = {
    {Vec2(SIM_WIDTH_IN_METERS - (SIM_WIDTH_IN_METERS * 0.03f), SIM_HEIGHT_IN_METERS * 0.8f),     Vec2(-SIM_WIDTH_IN_METERS * 0.75f, 0.0f)},
    {Vec2(SIM_WIDTH_IN_METERS * 0.03f, SIM_HEIGHT_IN_METERS * 0.8f),                             Vec2(SIM_WIDTH_IN_METERS * 0.75f, 0.0f)},
    {Vec2(SIM_WIDTH_IN_METERS - (SIM_WIDTH_IN_METERS * 0.03f), (SIM_HEIGHT_IN_METERS * 0.95f)),  Vec2(-SIM_WIDTH_IN_METERS * 0.75f, -SIM_HEIGHT_IN_METERS * 0.15f)},
    {Vec2(SIM_WIDTH_IN_METERS * 0.03f, SIM_HEIGHT_IN_METERS * 1.1f),                             Vec2(SIM_WIDTH_IN_METERS * 0.75f, -SIM_HEIGHT_IN_METERS * 0.75f)},
    {Vec2(SIM_WIDTH_IN_METERS * 0.5f, SIM_HEIGHT_IN_METERS * 1.5f),                              Vec2(0.0f, -SIM_HEIGHT_IN_METERS * 1.5f)},
};

static unsigned char cannon_ball_colors[][3] = {        // [0]: R, [1]: G, [2]: B
    {255, 100, 100},
    {100, 100, 255},
    {100, 255, 100},
    {255, 255, 20},
};

std::vector<Ball> Level::balls;
int Level::number_of_balls_shot = 0;

Level::Level(const level_configs_t level_configs, user_input_t *user_input)
{
    this->user_input = user_input;
    this->configs = level_configs;

    setup();
}

Level::~Level() 
{
    delete[] cannons;
    delete[] cannon_configs;
}

void Level::setup(void) 
{ 
    balls.clear();
    number_of_balls_shot = 0;
    bucket.init(Vec2(0.0f, 0.0f), 2.0f, 3.0f, 1.0f, RED);

    cannons = new Cannon[configs.n_cannons];
    cannon_configs = new cannon_configs_t[configs.n_cannons];

    for (int cannon = 0; cannon < configs.n_cannons; cannon++)
    {
        cannon_configs[cannon].pos = cannon_starting_positions[cannon][0];
        cannon_configs[cannon].direction = cannon_starting_positions[cannon][1];
        cannon_configs[cannon].time_between_shots_s = (configs.base_time_between_shots_ms + RNG::getValue(0, 50)) / 1000.0f;
        cannon_configs[cannon].ball_limit = configs.n_balls_per_cannon;
        cannon_configs[cannon].min_ball_radius = configs.ball_radius_min;
        cannon_configs[cannon].max_ball_radius = configs.ball_radius_max;
        cannon_configs[cannon].color = WHITE;

        // only the first cannon should have valid colored balls
        if (cannon != 0)
        {
            cannon_configs[cannon].color.r = cannon_ball_colors[cannon - 1][0];
            cannon_configs[cannon].color.g = cannon_ball_colors[cannon - 1][1];
            cannon_configs[cannon].color.b = cannon_ball_colors[cannon - 1][2];
            cannon_configs[cannon].color.a = 255;
        }

        cannons[cannon].init(&cannon_configs[cannon]);
    }
}

void Level::print_scoring_balls_on_screen(void)
{
    std::string str = std::to_string(scoring_balls_on_screen);
    DrawText(str.c_str(), 10, SCREEN_HEIGHT - 20, 20, WHITE);

    std::string str2 = std::to_string(non_scoring_balls_on_screen);
    DrawText(str2.c_str(), 50, SCREEN_HEIGHT - 20, 20, YELLOW);
}

void Level::register_new_ball(Ball ball)
{
    balls.push_back(ball);
    number_of_balls_shot++;
}

bool Level::have_finished(void)
{
    bool ret = false;

    if (number_of_balls_shot == (configs.n_cannons * configs.n_balls_per_cannon))
    {
        if ((scoring_balls_on_screen == 0 && non_scoring_balls_on_screen == 0) || 
             scoring_balls_on_screen < configs.level_number)
        {
            ret = true;
        }
        else
        {
            int balls_inside_bucket = 0;
            for (size_t i = 0; i < balls.size(); i++)
            {
                balls_inside_bucket += static_cast<int>(is_ball_inside_bucket(balls[i], bucket));
            }

            if (configs.mode == LEVEL_MODE_EASY)
            {
                ret = (balls_inside_bucket >= configs.level_number) && non_scoring_balls_on_screen == 0;
            }
            else if (configs.mode == LEVEL_MODE_HARD)
            {
                ret = (balls_inside_bucket == configs.level_number) && non_scoring_balls_on_screen == 0;
            }
        }
    }

    return ret;
}

bool Level::won(void)
{
    bool was_level_won = false;

    if (configs.mode == LEVEL_MODE_EASY) was_level_won = (scoring_balls_on_screen >= configs.level_number);
    else if (configs.mode == LEVEL_MODE_HARD) was_level_won = (scoring_balls_on_screen == configs.level_number);

    return was_level_won;
}

void Level::loop()
{
    if(!have_finished())
    {
        for (int i = 0; i < configs.n_cannons; i++)
        {
            cannons[i].update();
        }
        
        bucket.update(user_input->position_on_x_axis, user_input->position_on_y_axis);
        scoring_balls_on_screen = 0;
        non_scoring_balls_on_screen = 0;

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

            if (balls[i].color.r == SCORING_BALL_COLOR_R &&
                balls[i].color.g == SCORING_BALL_COLOR_G &&
                balls[i].color.b == SCORING_BALL_COLOR_B &&
                balls[i].color.a == SCORING_BALL_COLOR_A)
            {
                scoring_balls_on_screen++;
            }
            else
            {
                non_scoring_balls_on_screen++;
            }
        }

        bucket.draw();
        // print_scoring_balls_on_screen();
    }
    else
    {
        for (size_t i = 0; i < balls.size(); i++)
        {
            balls[i].draw();
        }
        bucket.draw();
        // print_scoring_balls_on_screen();
    }

    std::string level_number = "Level: " + std::to_string(configs.level_number);
    DrawText(level_number.c_str(), SCREEN_WIDTH - 90, 10, 20, WHITE);
}
