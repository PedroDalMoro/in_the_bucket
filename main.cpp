#include <iostream>
#include <raylib.h>

#include "defs.hpp"
#include "balde.hpp"
#include "bola.hpp"

#define N_BOLAS     100             // definitivamente não tem 100 bolinhas na tela atualmente, agora onde tão elas eu não sei. 

int main () 
{
    SetRandomSeed(123);

    Balde balde(40, 80, GREEN);
    // Bola bola(10, 5, 0.2, WHITE);

    Bola bolas[N_BOLAS];
    for (size_t i = 0; i < N_BOLAS; i++)
    {
        float x = i * 0.77f;
        float y = i * 0.55f;
        float r = i * 0.02f;

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
        ClearBackground(DARKBLUE);

        int mouse_x = GetMouseX();
        int mouse_y = SCREEN_HEIGHT - 80;
        balde.draw(mouse_x, mouse_y);

        for (size_t i = 0; i < N_BOLAS; i++)
        {
            bolas[i].update();
            bolas[i].draw();
        }

        // bola.update();
        // bola.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}