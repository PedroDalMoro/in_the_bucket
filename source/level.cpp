#include "level.hpp"

#include "rng.hpp"
#include "physics.hpp"

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
    balls = new Ball[configs.n_balls];

    for (size_t i = 0; i < configs.n_balls; i++)
    {
        float x = static_cast<float>(SIM_WIDTH_IN_METERS) * RNG::getNormalized();
        float y = SIM_HEIGHT_IN_METERS - (5.0f * RNG::getNormalized());
        float r = configs.ball_radius_min + (configs.ball_radius_max * RNG::getNormalized());
        float vx = 5.0f * RNG::getNormalized();
        float vy = 5.0f * RNG::getNormalized();
        Color color = RNG::getValue(0, 1) ? configs.color_valid : configs.color_invalid;

        balls[i].init(x, y, vx, vy, r, r * r * PI, color);
    }    

    bucket.init(Vec2(0.0f, 0.0f), 2.0f, 3.0f, 1.0f, RED);
}

void Level::loop()
{
    bucket.update(user_input->position_on_x_axis, user_input->position_on_y_axis);

    for (size_t i = 0; i < configs.n_balls; i++)
    {
        balls[i].update();

        // isso pode ser melhorado com hashing pra não ser chamado pra todas as bolinhas
        for(size_t j = i + 1; j < configs.n_balls; j++)
        {
            handle_ball_collision(balls[i], balls[j], 0.707f);
        }

        handle_bar_collision(bucket.bar_left, balls[i]);
        handle_bar_collision(bucket.bar_bottom, balls[i]);
        handle_bar_collision(bucket.bar_right, balls[i]);
        balls[i].draw();
    }

    bucket.draw();
}

