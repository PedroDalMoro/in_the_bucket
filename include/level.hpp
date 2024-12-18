#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <raylib.h>
#include "ball.hpp"
#include "bucket.hpp"
#include "defs.hpp"

struct level_configs_t {
    size_t n_balls;
    Color color_valid;
    Color color_invalid;
    float ball_radius_min;
    float ball_radius_max;
};

class Level {
private:
    Ball *balls;
    Bucket bucket;
    level_configs_t configs;
    user_input_t *user_input;
    
    void setup(void);
    
public:
    Level(const level_configs_t level_configs, user_input_t *user_input);
    ~Level();

    void loop();
};

#endif // LEVEL_HPP
