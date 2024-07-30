#include <iostream>
#include <raylib.h>

#include "defs.hpp"
#include "balde.hpp"
#include "bola.hpp"

#define N_BOLAS 1000

int main () 
{
    Balde balde(40, 80, GREEN);
    Bola bolas[N_BOLAS];

    SetRandomSeed(23);

    for (size_t i = 0; i < N_BOLAS; i++)
    {
        int x = GetRandomValue(1, SCREEN_WIDTH);
        int y = GetRandomValue(20, SCREEN_HEIGHT);
        float r = GetRandomValue(5, 30);
        Color color = {
            .r = (unsigned char)GetRandomValue(0, 255),
            .g = (unsigned char)GetRandomValue(0, 255),
            .b = (unsigned char)GetRandomValue(0, 255),
            .a = (unsigned char)GetRandomValue(100, 255)
        };
        bolas[i].init(x, y, r, color);
    }
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TornadoBol");
    SetTargetFPS(FPS_TARGET);

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(GRAY);

        int mouse_x = GetMouseX();
        int mouse_y = SCREEN_HEIGHT - 80;
        balde.draw(mouse_x, mouse_y);

        for (size_t i = 0; i < N_BOLAS; i++)
        {
            bolas[i].update();
            bolas[i].draw();
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}