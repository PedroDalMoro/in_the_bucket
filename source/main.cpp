#include <iostream>
#include <raylib.h>

#include "defs.hpp"
#include "bucket.hpp"
#include "ball.hpp"
#include "bar.hpp"
#include "rng.hpp"
#include "physics.hpp"

#include <math.h>

#define N_BALLS    1

void print_number(float number_to_print, int x, int y)
{
    std::string str = std::to_string(number_to_print);
    DrawText(str.c_str(), x, y, 20, WHITE);
}

int main () 
{
    RNG random;

    Ball balls[N_BALLS];
    for (size_t i = 0; i < N_BALLS; i++)
    {
        float x = static_cast<float>(SIM_WIDTH_IN_METERS) * random.getNormalized();
        float y = SIM_HEIGHT_IN_METERS - (5.0f * random.getNormalized());
        float r = 0.15f + (0.5f * random.getNormalized());
        float vx = 5.0f * random.getNormalized();
        float vy = 5.0f * random.getNormalized();

        Color color = {
            .r = (unsigned char)random.getValue(0, 255),
            .g = (unsigned char)random.getValue(0, 255),
            .b = (unsigned char)random.getValue(0, 255),
            .a = (unsigned char)random.getValue(100, 255)
        };
        balls[i].init(x, y, vx, vy, r, r * r * PI, color);
    }

    float move_x = 5.0f;
    float move_y = 5.0f;
    Bucket bucket(Vec2(move_x, move_y), 2.0f, 3.0f, 1.0f, RED);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TornadoBol");

    float other_x = 5.0f;
    float other_y = 5.0f;

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        if (IsKeyDown(KEY_LEFT)) move_x -= 0.003f;    
        if (IsKeyDown(KEY_RIGHT)) move_x += 0.003f;
        if (IsKeyDown(KEY_UP)) move_y += 0.003f;
        if (IsKeyDown(KEY_DOWN)) move_y -= 0.003f;
        bucket.draw(move_x, move_y);

        for (size_t i = 0; i < N_BALLS; i++)
        {
            balls[i].update();

            // isso pode ser melhorado com hashing pra não ser chamado pra todas as bolinhas
            for(size_t j = i + 1; j < N_BALLS; j++)
            {
                handle_ball_collision(balls[i], balls[j], 0.707f);
            }

            handle_bar_collision(bucket.bar1, balls[i]);
            handle_bar_collision(bucket.bar2, balls[i]);
            handle_bar_collision(bucket.bar3, balls[i]);
            balls[i].draw();
        }

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