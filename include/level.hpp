#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <raylib.h>
#include <vector>

#include "ball.hpp"
#include "bucket.hpp"
#include "defs.hpp"
#include "cannon.hpp"

// scoring ball will be WHITE
#define SCORING_BALL_COLOR_R    0xFF
#define SCORING_BALL_COLOR_G    0xFF
#define SCORING_BALL_COLOR_B    0xFF
#define SCORING_BALL_COLOR_A    0xFF

struct level_configs_t {
    size_t n_balls;
    Color color_valid;
    Color color_invalid;
    float ball_radius_min;
    float ball_radius_max;
};

class Level {
    friend class Cannon;

private:
    level_configs_t configs;
    user_input_t *user_input;
    int scoring_balls_on_screen;

    Cannon cannon;
    cannon_configs_t cannon_configs;

    Cannon cannon2;
    cannon_configs_t cannon2_configs;

    Bucket bucket;
    static std::vector<Ball> balls;
    
    void setup(void);
    void print_scoring_balls_on_screen(void);
    
public:
    Level(const level_configs_t level_configs, user_input_t *user_input);
    ~Level();

    static void register_new_ball(Ball ball);
    void loop();
};

#endif // LEVEL_HPP
