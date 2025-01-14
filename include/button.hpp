// NOTE: por algum motivo, se tenho vários botões perto um do outro, o clique neles se soberscreve. 
// Acho que pode ter algo a ver com o jeito que estou lidando com as conversões de medidas entre pixels e 
// metros. Quem sabe pra essas coisas que não são realmente físicas (botões, sliders), eu poderia usar somente pixels mesmo.

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
    BUTTON_TYPE_LATCH,              // botão do tipo trava, alterna entre o estado ON e OFF
    BUTTON_TYPE_MOMENTARY           // botão do tipo momentâneo, retorna apenas uma vez o estado ON
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