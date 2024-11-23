#include <iostream>
#include <raylib.h>

#include "defs.hpp"
#include "balde.hpp"
#include "bola.hpp"
#include "bar.hpp"
#include "rng.hpp"
#include "physics.hpp"

#define N_BOLAS     4

void print_number(float number_to_print, int x, int y)
{
    std::string str = std::to_string(number_to_print);
    DrawText(str.c_str(), x, y, 20, WHITE);
}

int main () 
{
    RNG random;
    Balde balde(40, 80, GREEN);

    Bola bolas[N_BOLAS];
    for (size_t i = 0; i < N_BOLAS; i++)
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
        bolas[i].init(x, y, vx, vy, r, r * r * PI, color);
    }

    Vec2 start(4, 8);
    Vec2 end(8, 4);
    Bar bar(start, end, 0.5f, WHITE);

    Vec2 start2(12, 8);
    Vec2 end2(8, 4);
    Bar bar2(start2, end2, 0.5f, WHITE);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TornadoBol");

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        int mouse_x = GetMouseX();
        int mouse_y = SCREEN_HEIGHT - 80;

        balde.draw(mouse_x, mouse_y);
        bar.draw();
        bar2.draw();

        for (size_t i = 0; i < N_BOLAS; i++)
        {
            bolas[i].update();

            // isso pode ser melhorado com hashing pra não ser chamado pra todas as bolinhas
            for(size_t j = i + 1; j < N_BOLAS; j++)
            {
                handle_ball_collision(bolas[i], bolas[j], 0.707f);
            }

            handle_bar_collision(bar, bolas[i]);
            handle_bar_collision(bar2, bolas[i]);
            bolas[i].draw();
        }

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}