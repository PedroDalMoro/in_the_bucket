#include <iostream>
#include <raylib.h>

#include "defs.hpp"
#include "bucket.hpp"
#include "ball.hpp"
#include "bar.hpp"
#include "rng.hpp"
#include "physics.hpp"
#include "level.hpp"

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

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        if (IsKeyDown(KEY_LEFT)) user_input.position_on_x_axis -= 0.003f;    
        if (IsKeyDown(KEY_RIGHT)) user_input.position_on_x_axis += 0.003f;
        if (IsKeyDown(KEY_UP)) user_input.position_on_y_axis += 0.003f;
        if (IsKeyDown(KEY_DOWN)) user_input.position_on_y_axis -= 0.003f;

        level.loop();

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

/*
    A situação agora é a seguinte: não quero simplesmente largar isso no meio, mas quero terminar ele logo. 
    Como foi só eu mesmo que lidei nisso desde o começo, e tenho outras coisas que quero estudar no momento, o plano pra finalizar 
    o joguinho vai ser:
    - manter somente as setas pra mexer o balde, porque assim não tem o problema das bolinhas saírem pelo meio dele
    - arrumar a estrutura desse projeto, porque isso seria algo que eu gostaria de aprender e seria útil
    - criar uns sliders que podem servir pra montar os níveis (o jogo em si pode ter só um nível main, onde as coisas mudam conforme os sliders e possivelmente
    um botão de reset)
    - colocar contador de bolas na tela e também fazer com que as bolas que estão fora saiam do escopo do jogo (aprender a lidar com o new e delete melhor)
    - tentar implementar os easings no movimento do balde, acho que seria legal e fácil - já não sei até que ponto seria fácil, só legal mesmo
*/