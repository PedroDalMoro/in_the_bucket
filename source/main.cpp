#include <iostream>
#include <raylib.h>

#include "defs.hpp"
#include "balde.hpp"
#include "bola.hpp"
#include "rng.hpp"

#define N_BOLAS     100

int main () 
{
    RNG random;
    Balde balde(40, 80, GREEN);

    Bola bolas[N_BOLAS];
    for (size_t i = 0; i < N_BOLAS; i++)
    {
        float x = static_cast<float>(SIM_WIDTH_IN_METERS) * random.getNormalized();
        float y = SIM_HEIGHT_IN_METERS - (5.0f * random.getNormalized());
        float r = 0.05f + (0.5f * random.getNormalized());
        float vx = 5.0f * random.getNormalized();
        float vy = 5.0f * random.getNormalized();

        Color color = {
            .r = (unsigned char)random.getValue(0, 255),
            .g = (unsigned char)random.getValue(0, 255),
            .b = (unsigned char)random.getValue(0, 255),
            .a = (unsigned char)random.getValue(100, 255)
        };
        bolas[i].init(x, y, vx, vy, r, color);
    }
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TornadoBol");
    SetTargetFPS(FPS_TARGET);

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(DARKBROWN);

        int mouse_x = GetMouseX();
        int mouse_y = SCREEN_HEIGHT - 80;
        balde.draw(mouse_x, mouse_y);

        for (size_t i = 0; i < N_BOLAS; i++)
        {
            bolas[i].update();
            bolas[i].draw();
        }

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}