#include <iostream>
#include <raylib.h>

#include "defs.hpp"
#include "balde.hpp"
#include "bola.hpp"
#include "rng.hpp"

#define N_BOLAS     30

void handle_ball_collision(Bola& b1, Bola& b2, float coef_resitution)
{
    // verifica se as duas bolas estão colidindo entre si e retorna caso não estejam
    Vec2 direction = Vec2::getVectorSubtraction(b2.pos, b1.pos);
    float distance = direction.getLength();

    if((distance == 0.0) || (distance > (b1.rad + b2.rad)))
    {
        return;
    }

    // se estão colidindo, calcula qual tem que ser a correção (quanto afastar uma da outra)
    float correction = (b1.rad + b2.rad - distance) / 2.0f;

    // normaliza a direção pra ser só a direção, e não importar o tamanho
    direction = direction.getNormalized();

    // calcula as novas posições das bolas, adicionando pro vetor delas o tamanho da 
    // correção na direção do vetor direction (normalizado antes)
    Vec2 newpos_b1 = Vec2::getVectorScaled(direction, -correction);
    b1.pos.add(newpos_b1);

    // NOTE: quando esqueci e deixei o sinal desse correction negativo, funcionava
    // errado mas de um jeito legal kkkkk pode ser algo do jogo no futuro
    Vec2 newpos_b2 = Vec2::getVectorScaled(direction, correction);
    b2.pos.add(newpos_b2);

    // o dot product é basicamente quão parecidos são dois vetores. Se o resultado for 1, são iguais. 
    // se for -1, são completamente opostos. Então pelo meu entendimento o que tá sendo calculado aqui
    // é o quão parecidas são a velocidade atual da bola e a direção do impacto entre as duas
    float v1 = b1.vel.dotProduct(direction);
    float v2 = b2.vel.dotProduct(direction);

    float m1 = b1.mass;
    float m2 = b2.mass;

    // calcula as novas velocidades depois da colisão, e aplica elas pras duas bolas
    float new_v1 = ((m1 * v1) + (m2 * v2) - ( m2 * (v1 - v2) * coef_resitution)) / (m1 + m2);
    float new_v2 = ((m1 * v1) + (m2 * v2) - ( m1 * (v2 - v1) * coef_resitution)) / (m1 + m2);

    Vec2 newvel_b1 = Vec2::getVectorScaled(direction, new_v1 - v1);
    b1.vel.add(newvel_b1);

    Vec2 newvel_b2 = Vec2::getVectorScaled(direction, new_v2 - v2);
    b2.vel.add(newvel_b2);
}

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
        bolas[i].init(x, y, vx, vy, r, color);
    }
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TornadoBol");
    SetTargetFPS(FPS_TARGET);

asdf
    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        int mouse_x = GetMouseX();
        int mouse_y = SCREEN_HEIGHT - 80;
        balde.draw(mouse_x, mouse_y);

        for (size_t i = 0; i < N_BOLAS; i++)
        {
            bolas[i].update();

            // isso pode ser melhorado com hashing pra não ser chamado pra todas as bolinhas
            for(size_t j = i + 1; j < N_BOLAS; j++)
            {
                handle_ball_collision(bolas[i], bolas[j], 0.707f);
            }

            bolas[i].draw();
        }

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}