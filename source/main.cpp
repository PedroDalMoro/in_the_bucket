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

#define N_BALLS 10

void print_number(float number_to_print, int x, int y)
{
    std::string str = std::to_string(number_to_print);
    DrawText(str.c_str(), x, y, 20, WHITE);
}

int main()
{
    RNG::init();
    user_input_t user_input = {5.0f, 5.0f};

    Level *level = nullptr;
    level_configs_t level_configs;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TornadoBol");

    // momento pra escolher o level, ver melhor depois
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        DrawText("Chose mode:", 10, 40, 20, WHITE);
        DrawText("E - Easy", 10, 70, 20, WHITE);
        DrawText("H - Hard", 10, 100, 20, WHITE);
        DrawText("S - Sandbox", 10, 130, 20, WHITE);
        DrawText("ESC - Exit", 10, 160, 20, WHITE);

        if (IsKeyDown(KEY_E))
        {
            level_configs.level_number = 1;
            level_configs.n_cannons = 2;
            level_configs.n_balls_per_cannon = 10;
            level_configs.base_time_between_shots_ms = 300;
            level_configs.ball_radius_min = 0.2f;
            level_configs.ball_radius_max = 0.3f;
            level_configs.mode = LEVEL_MODE_EASY;

            level = new Level(level_configs, &user_input);
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

    // antes de começar, cria o novo level com as configurações iniciais básicas

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        if (IsKeyDown(KEY_LEFT)) user_input.position_on_x_axis -= 0.003f;
        if (IsKeyDown(KEY_RIGHT)) user_input.position_on_x_axis += 0.003f;
        if (IsKeyDown(KEY_UP)) user_input.position_on_y_axis += 0.003f;
        if (IsKeyDown(KEY_DOWN)) user_input.position_on_y_axis -= 0.003f;

        level->loop();

        DrawFPS(10, 10);
        EndDrawing();

        if (level->have_finished())
        {
            if (level->won())
            {
                DrawText("Level Cleared!", 10, 40, 20, DARKGREEN);
            }
            else
            {
                DrawText("Level Failed!", 10, 40, 20, DARKPURPLE);
            }
        }
    }

    // depois de terminar, caso tenha ganho o level, delete aquele e seta novas configurações (pode ser meio random baseado no número do level?)

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