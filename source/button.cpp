#include "button.hpp"
#include "engine.hpp"

Button::Button()
{

}

Button::Button(Vec2 pos, std::string text, button_type_t type, bool status, float width)
{
    init(pos, text, type, status, width);
}

Button::~Button()
{
}

void Button::init(Vec2 pos, std::string text, button_type_t type, bool status, float width)
{
    this->pos = pos;
    this->type = type;
    this->status = status;
    this->already_returned_true = false;
    this->color = BUTTON_COLOR_ON;
    this->last_click_timestamp = 0.0;
    this->text = text;
    this->width = width;
}

void Button::update(void)
{
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        int mouse_x = GetMouseX();
        int mouse_y = GetMouseY();

        if ((mouse_x > map_meters_to_pixel_x(pos.x)) && 
            (mouse_x < map_meters_to_pixel_x(pos.x + width)) &&
            (mouse_y > map_meters_to_pixel_y(pos.y + BUTTON_HEIGHT)) &&
            (mouse_y < map_meters_to_pixel_y(pos.y - BUTTON_HEIGHT)))
        {

            if (type == BUTTON_TYPE_LATCH)
            {
                double time_since_last_click = GetTime() - last_click_timestamp;
                if (time_since_last_click > BUTTON_DEBOUNCE_S)
                {
                    status = !status;
                    color = status ? BUTTON_COLOR_OFF : BUTTON_COLOR_ON;
                    last_click_timestamp = GetTime();
                }
            }
            else if (type == BUTTON_TYPE_MOMENTARY)
            {
                status = already_returned_true ? false : true;
                color = BUTTON_COLOR_OFF;
            }
        }
    }
    else
    {
        if (type == BUTTON_TYPE_MOMENTARY)
        {
            status = false;
            already_returned_true = false;
            color = BUTTON_COLOR_ON;
        }
    } 
}

bool Button::get_status(void)
{
    bool ret = status;

    if (type == BUTTON_TYPE_MOMENTARY && status)
    {
        ret = !already_returned_true;
        already_returned_true = true;
    }

    return ret;
}

void Button::draw(void)
{
    DrawRectangle(map_meters_to_pixel_x(pos.x), 
                    map_meters_to_pixel_y(pos.y), 
                    map_meters_to_pixel_x(width), 
                    map_meters_to_pixel_x(BUTTON_HEIGHT),       // mapeando os dois com a função de x porque é a que não aplica mudanças
                    color);

    DrawText(text.c_str(),
            map_meters_to_pixel_x(pos.x + 0.15f), 
            map_meters_to_pixel_y(pos.y - 0.25f), 
            20, 
            BLACK);
}