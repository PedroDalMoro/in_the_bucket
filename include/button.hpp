/*
    NOTE: This button class ended up not being used, and probably didn't work as well as I would have liked...

    For some reason, if I have several buttons close to each other, clicking on them overrides each other.
    I think it might have something to do with the way I'm handling the conversions between pixels and
    meters. Maybe for these things that aren't really physical (buttons, sliders), I could just use pixels.
*/
#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
#include <raylib.h>
#include "vector_2.hpp"

#define BUTTON_WIDTH        1.8f
#define BUTTON_HEIGHT       1.0f
#define BUTTON_COLOR_ON     WHITE
#define BUTTON_COLOR_OFF    GRAY
#define BUTTON_DEBOUNCE_S   1.0

typedef enum {
    BUTTON_TYPE_LATCH,              // switches between ON and OFF states
    BUTTON_TYPE_MOMENTARY           // returns only once the ON state
} button_type_t;

class Button
{
private:
    Vec2 pos;
    bool status;
    bool already_returned_true;
    Color color;
    button_type_t type;
    double last_click_timestamp;
    std::string text;
    float width;

public:
    Button();
    Button(Vec2 pos, std::string text, button_type_t type = BUTTON_TYPE_LATCH, bool status = false, float width = BUTTON_WIDTH);
    ~Button();

    void init(Vec2 pos, std::string text, button_type_t type = BUTTON_TYPE_LATCH, bool status = false, float width = BUTTON_WIDTH);
    void update(void);
    bool get_status(void);
    void draw(void);
};

#endif // BUTTON_HPP