#include <iostream>
#include <raylib.h>

#include "balde.hpp"

#define SCREEN_HEIGHT   600
#define SCREEN_WIDTH    800

int main () 
{
    Balde balde(40, 80, GREEN);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TornadoBol");
    SetTargetFPS(60);

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(GRAY);

        int mouse_x = GetMouseX();
        int mouse_y = SCREEN_HEIGHT - 80;
        balde.draw(mouse_x, mouse_y);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}