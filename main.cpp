#include <iostream>
#include <raylib.h>

#define SCREEN_HEIGHT   600
#define SCREEN_WIDTH    800

int main () 
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TornadoBol");
    SetTargetFPS(60);

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(GRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}