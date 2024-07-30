#include <iostream>
#include <raylib.h>

#include "defs.hpp"
#include "balde.hpp"
#include "bola.hpp"

int main () 
{
    Balde balde(40, 80, GREEN);
    Bola bola(200, 300, 10);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TornadoBol");
    SetTargetFPS(FPS_TARGET);

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(GRAY);

        int mouse_x = GetMouseX();
        int mouse_y = SCREEN_HEIGHT - 80;
        balde.draw(mouse_x, mouse_y);

        bola.update();
        bola.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}