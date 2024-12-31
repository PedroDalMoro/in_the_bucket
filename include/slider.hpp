#ifndef SLIDER_HPP
#define SLIDER_HPP

#include "vector_2.hpp"
#include "ball.hpp"

#define SLIDER_LENGTH 4.0f
#define SLIDER_HEIGHT 0.1f

typedef enum {
    SLIDER_POS_1,
    SLIDER_POS_2,
    SLIDER_POS_3,
} slider_pos_t;

class Slider
{
private:
    Vec2 start_pos;
    Vec2 end_pos_total;
    Vec2 end_pos_marker;
    bool is_enabled;
    float percentage_value;

    void init(Vec2 pos, bool is_enabled = true);
    void print_value(float value);

public:
    Slider();
    Slider(slider_pos_t pos, bool is_enabled = true);
    ~Slider();

    float get_percentage_value(void);
    void update(void);
    void draw(void);
};



#endif // SLIDER_HPP