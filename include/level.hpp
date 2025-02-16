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

typedef enum {
    LEVEL_MODE_EASY,
    LEVEL_MODE_HARD,
    LEVEL_MODE_SANDBOX
}level_mode_t;

struct level_configs_t {
    int level_number;
    int n_cannons;
    int n_balls_per_cannon;
    int base_time_between_shots_ms;
    float ball_radius_min;
    float ball_radius_max;
    level_mode_t mode;
};

class Level {
    friend class Cannon;

private:
    level_configs_t configs;
    user_input_t *user_input;
    Bucket bucket;
    Cannon *cannons;
    cannon_configs_t *cannon_configs;

    static std::vector<Ball> balls;
    static int number_of_balls_shot;

    int scoring_balls_on_screen;
    int non_scoring_balls_on_screen;
    int extra_scoring_balls;
    
    void setup(void);
    void print_scoring_balls_on_screen(void);
    
public:
    Level(const level_configs_t level_configs, user_input_t *user_input);
    ~Level();

    static void register_new_ball(Ball ball);
    bool won(void);
    bool have_finished(void);
    void loop();
};

#endif // LEVEL_HPP
