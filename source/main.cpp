#include <iostream>
#include <raylib.h>

#include "defs.hpp"
#include "bucket.hpp"
#include "ball.hpp"
#include "bar.hpp"
#include "rng.hpp"
#include "engine.hpp"
#include "level.hpp"
#include "slider.hpp"

#define N_BALLS    10

void print_number(float number_to_print, int x, int y)
{
    std::string str = std::to_string(number_to_print);
    DrawText(str.c_str(), x, y, 20, WHITE);
}

int main () 
{
    RNG::init();
    user_input_t user_input = {5.0f, 5.0f};

    level_configs_t level_configs = {
        .n_balls = N_BALLS,
        .color_valid = WHITE,
        .color_invalid = RED,
        .ball_radius_min = 0.25f,
        .ball_radius_max = 0.40f
    };

    Level level(level_configs, &user_input);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TornadoBol");

    Slider slider(SLIDER_POS_1);
    Slider slider2(SLIDER_POS_2, false);
    Slider slider3(SLIDER_POS_3);

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        if (IsKeyDown(KEY_LEFT)) user_input.position_on_x_axis -= 0.003f;    
        if (IsKeyDown(KEY_RIGHT)) user_input.position_on_x_axis += 0.003f;
        if (IsKeyDown(KEY_UP)) user_input.position_on_y_axis += 0.003f;
        if (IsKeyDown(KEY_DOWN)) user_input.position_on_y_axis -= 0.003f;

        level.loop();

        slider.update();
        slider.draw();
        slider2.update();
        slider2.draw();
        slider3.update();
        slider3.draw();

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

/*
    Coisas que faltam, versão simplificada:
    - criar estrutura pra ter mais levels (mais pro final isso)
    - criar botão
    - criar sliders
    - criar canhão
    - criar contador de bolas na tela (fazer isso com new e delete afu)
    - tentar implementar velocidade do balde (pra se bater nas bolinhas também)
*/