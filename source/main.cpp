/**
 * @author Pedro Dal Moro (pedrocentenaro22@gmail.com)
 * 
 * @brief This project was born with the goal of helping me learn C++ with something that interested me,
 * and to bring me and my friends together in this development. One of the goals was successfully completed!
 * 
 * I am sure that many things are not perfect, it is not the best game in the world and it would not
 * keep someone playing it for more than a few minutes (and that is probably good so that the memory leaks
 * are not discovered), but my current thought is:
 * 
 * FINISH YOUR FUCKING PROJECTS!
 * 
 * So, with this thought in mind, I know that I managed to build something very similar to what I had
 * in mind at the beginning, and learn a lot about C++, unit tests, makefiles, CI/CD, physics simulation for
 * games, and many other things. Who knows, maybe one day I will return to improve something or continue what
 * I started (probably not), but anyway I am happy to have at least reached somewhere without abandoning the project halfway!
 * 
 * @version 1.0
 * @date 16-02-2025
 */
#include <raylib.h>
#include "defs.hpp"
#include "rng.hpp"
#include "level.hpp"

static bool wait_for_key_press(int key);
static void setup_new_level(level_configs_t &level_configs, user_input_t &user_input, int level_number, level_mode_t mode);
static void chose_mode(level_configs_t &level_configs, user_input_t &user_input);

static Level *level = nullptr;
static bool start_menu = true;
static int current_level = 1;

int main()
{
    RNG::init();
    user_input_t user_input = {5.0f, 5.0f};
    level_configs_t level_configs;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TornadoBol");

    while (!WindowShouldClose())
    {
        // block until level mode is selected
        if (start_menu) chose_mode(level_configs, user_input);

        // this is the game loop
        BeginDrawing();
        ClearBackground(BLACK);

        float dt = GetFrameTime();
        float movement_update = dt / 0.075;   // this is a magic value, tweeked until it felt right

        if (IsKeyDown(KEY_LEFT)) user_input.position_on_x_axis -= movement_update;
        if (IsKeyDown(KEY_RIGHT)) user_input.position_on_x_axis += movement_update;
        if (IsKeyDown(KEY_UP)) user_input.position_on_y_axis += movement_update;
        if (IsKeyDown(KEY_DOWN)) user_input.position_on_y_axis -= movement_update;

        level->loop();
        DrawFPS(10, 10);
        
        if (level->have_finished())
        {
            if (level->won())
            {
                DrawText("Level Cleared! Press SPACEBAR to continue.", 10, 40, 20, GREEN);
                if (wait_for_key_press(KEY_SPACE))
                {
                    level_mode_t mode = level_configs.mode;
                    current_level++;
                    
                    delete level;
                    setup_new_level(level_configs, user_input, current_level, mode);
                }
            }
            else
            {
                DrawText("Level Failed! Press SPACEBAR to go back to menu.", 10, 40, 20, PURPLE);
                if (wait_for_key_press(KEY_SPACE))
                {
                    delete level;
                    start_menu = true;
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

static bool wait_for_key_press(int key)
{
    return IsKeyPressed(key);
}

static void setup_new_level(level_configs_t &level_configs, user_input_t &user_input, int level_number, level_mode_t mode)
{
    level_configs.level_number = level_number;
    level_configs.n_balls_per_cannon = 10 + (level_number * 3);
    level_configs.base_time_between_shots_ms = 500 - (RNG::getValue(level_number * 15, (level_number + 1) * 15));
    level_configs.ball_radius_min = 0.2f;
    level_configs.ball_radius_max = 0.4f;
    level_configs.mode = mode;

    int current_number_of_cannons = 2 + (level_number / 4);
    level_configs.n_cannons = current_number_of_cannons > 5 ? 5 : current_number_of_cannons;

    level = new Level(level_configs, &user_input);
}

static void chose_mode(level_configs_t &level_configs, user_input_t &user_input)
{
    current_level = 1;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Goal: Finish the level with the right number of WHITE balls inside the bucket!", 10, 40, 20, GRAY);
        DrawText("Chose mode:", 10, 100, 20, GRAY);
        DrawText("E - Easy (AT LEAST the same number of balls as the level number)", 10, 130, 20, GRAY);
        DrawText("H - Hard (EXACTLY the same number of balls as the level number)", 10, 160, 20, GRAY);
        DrawText("ESC - Exit", 10, 220, 20, GRAY);

        if (IsKeyDown(KEY_E))
        {
            setup_new_level(level_configs, user_input, current_level, LEVEL_MODE_EASY);
            EndDrawing();
            break;
        }
        
        else if (IsKeyDown(KEY_H))
        {
            setup_new_level(level_configs, user_input, current_level, LEVEL_MODE_HARD);
            EndDrawing();
            break;
        }

        DrawFPS(10, 10);
        EndDrawing();
    }

    start_menu = false;
}
