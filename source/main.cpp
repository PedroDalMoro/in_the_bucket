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
#include "button.hpp"
#include "cannon.hpp"

#include <iostream>
static Level *level = nullptr;
static bool start_menu = true;
static int current_level = 1;

void print_number(float number_to_print, int x, int y)
{
    std::string str = std::to_string(number_to_print);
    DrawText(str.c_str(), x, y, 20, WHITE);
}

bool wait_for_key_press(int key)
{
    return IsKeyPressed(key);
}

void setup_new_level(level_configs_t &level_configs, user_input_t &user_input, int level_number, level_mode_t mode)
{
    level_configs.level_number = level_number;
    level_configs.n_cannons = 2;
    level_configs.n_balls_per_cannon = 10 + (level_number * 2);
    level_configs.base_time_between_shots_ms = 400 - (RNG::getValue(0, level_number * 15));
    level_configs.ball_radius_min = 0.2f;
    level_configs.ball_radius_max = 0.3f;
    level_configs.mode = mode;

    level = new Level(level_configs, &user_input);
}

void chose_mode(level_configs_t &level_configs, user_input_t &user_input)
{
    current_level = 1;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Goal: Finish the level with the right number of WHITE balls inside the bucket!", 10, 40, 20, WHITE);
        DrawText("Chose mode:", 10, 100, 20, WHITE);
        DrawText("E - Easy (AT LEAST the same number of balls as the level number)", 10, 130, 20, WHITE);
        DrawText("H - Hard (EXACTLY the same number of balls as the level number)", 10, 160, 20, WHITE);
        DrawText("S - Sandbox", 10, 190, 20, WHITE);
        DrawText("ESC - Exit", 10, 220, 20, WHITE);

        if (IsKeyDown(KEY_E))
        {
            setup_new_level(level_configs, user_input, current_level, LEVEL_MODE_EASY);
            EndDrawing();
            break;
        }

        else if (IsKeyDown(KEY_H))
        {

        }

        else if (IsKeyDown(KEY_S))
        {

        }

        DrawFPS(10, 10);
        EndDrawing();
    }

    start_menu = false;
}

int main()
{
    RNG::init();
    user_input_t user_input = {5.0f, 5.0f};
    level_configs_t level_configs;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TornadoBol");

    while (!WindowShouldClose())
    {
        // block until level mode is selected
        if (start_menu) chose_mode(level_configs, user_input);

        // this is the game loop
        BeginDrawing();
        ClearBackground(BLACK);

        float dt = GetFrameTime();
        float movement_update = dt / 0.1;   // this is a magic value, tweeked until it felt right

        if (IsKeyDown(KEY_LEFT)) user_input.position_on_x_axis -= movement_update;
        if (IsKeyDown(KEY_RIGHT)) user_input.position_on_x_axis += movement_update;
        if (IsKeyDown(KEY_UP)) user_input.position_on_y_axis += movement_update;
        if (IsKeyDown(KEY_DOWN)) user_input.position_on_y_axis -= movement_update;

        level->loop();

        DrawFPS(10, 10);
        EndDrawing();

        if (level->have_finished())
        {
            if (level->won())
            {
                DrawText("Level Cleared! Press SPACEBAR to continue.", 10, 40, 20, GREEN);
                if (wait_for_key_press(KEY_SPACE))
                {
                    level_mode_t mode = level_configs.mode;
                    current_level++;

                    delete level;
                    setup_new_level(level_configs, user_input, current_level, mode);
                }
            }
            else
            {
                DrawText("Level Failed! Press SPACEBAR to go back to menu.", 10, 40, 20, PURPLE);
                if (wait_for_key_press(KEY_SPACE))
                {
                    delete level;
                    start_menu = true;
                }
            }
        }
    }

    CloseWindow();
    return 0;
}

/*
    A estrutura dos levels vai ser:

    Modo fácil:
    - o level sempre sobe de 1 em 1
    - no level N, pelo menos N bolas brancas tem que ficar na tela (dentro do balde) quando tudo acabar
    - número de bolas por level pode ir aumentando (ver ainda o tanto que faça sentido)

    Modo difícil:
    - mesma coisa, mas tem que conter exatamente N bolas no final 

    Modo sandbox
    - se eu estiver super afim, posso fazer isso, melhorar um pouco os botões e sliders e deixar a área de só se bobiar com as bolinhas um pouco 
    - eu quero acabar logo, mas agora to gostando, então dá pra passar um pouco mais de tempo nisso também 
*/