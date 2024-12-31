#include "slider.hpp"
#include "engine.hpp"
#include "defs.hpp"
#include "raylib.h"
#include <string>

Slider::Slider()
{
    
}

Slider::Slider(slider_pos_t pos, bool is_enabled)
{
    Vec2 top_left_point(SIM_WIDTH_IN_METERS - 4.5f, 0.0f);
    if (pos == SLIDER_POS_1) top_left_point.y = SIM_HEIGHT_IN_METERS - 0.5f;
    if (pos == SLIDER_POS_2) top_left_point.y = SIM_HEIGHT_IN_METERS - 1.0f;
    if (pos == SLIDER_POS_3) top_left_point.y = SIM_HEIGHT_IN_METERS - 1.5f;

    init(top_left_point, is_enabled);
}

Slider::~Slider()
{
}

void Slider::init(Vec2 pos, bool is_enabled)
{
    this->is_enabled = is_enabled;
    this->start_pos = pos;

    this->end_pos_total.x = pos.x + SLIDER_LENGTH;
    this->end_pos_total.y = pos.y;

    this->end_pos_marker.x = pos.x + SLIDER_LENGTH / 2.0f;
    this->end_pos_marker.y = pos.y;

    this->percentage_value = 0.5f;
}

void Slider::print_value(float value)
{
    std::string str = std::to_string(value);
    DrawText(str.c_str(), 
            map_meters_to_pixel_x(start_pos.x - 2.0f), 
            map_meters_to_pixel_y(start_pos.y + SLIDER_HEIGHT * 2.0f), 
            15, 
            WHITE);
}

float Slider::get_percentage_value(void)
{
    return percentage_value;
}

void Slider::update(void)
{
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        int mouse_x = GetMouseX();
        int mouse_y = GetMouseY();

        if ((mouse_x > map_meters_to_pixel_x(start_pos.x)) && 
            (mouse_x < map_meters_to_pixel_x(end_pos_total.x)) &&
            (mouse_y > map_meters_to_pixel_y(start_pos.y + SLIDER_HEIGHT)) &&
            (mouse_y < map_meters_to_pixel_y(start_pos.y - SLIDER_HEIGHT)))
        {
            this->end_pos_marker.x = map_pixel_to_meters_x(mouse_x);
            percentage_value = (end_pos_marker.x - start_pos.x) / SLIDER_LENGTH;
        }
    }
}

void Slider::draw(void)
{
    if (is_enabled)
    {
        DrawLineEx(map_point_to_pixel(start_pos), 
                    map_point_to_pixel(end_pos_total), 
                    map_radius_to_pixel(SLIDER_HEIGHT), 
                    WHITE);

        DrawLineEx(map_point_to_pixel(start_pos), 
                    map_point_to_pixel(end_pos_marker), 
                    map_radius_to_pixel(SLIDER_HEIGHT), 
                    GRAY);

        print_value(percentage_value);
    }
}