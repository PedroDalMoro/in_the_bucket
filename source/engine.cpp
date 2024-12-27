#include "engine.hpp"

void handle_ball_collision(Ball& b1, Ball& b2, float coef_resitution)
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

Vec2 get_closest_point_on_segment(Vec2 point, Vec2 seg_point_a, Vec2 seg_point_b)
{
    Vec2 seg = Vec2::getVectorSubtraction(seg_point_b, seg_point_a);
    float t = seg.dotProduct(seg);

    if (t == 0.0f)
    {
        return seg_point_a;
    }

    float calc = (point.dotProduct(seg) - seg_point_a.dotProduct(seg)) / t;
    t = fmax(0.0f, fmin(1.0f, calc));

    Vec2 closest_point = Vec2::getVectorScaled(seg, t);
    seg_point_a.add(closest_point);

    return seg_point_a;
}

void handle_bar_collision(Bar bar, Ball& bola)
{
    Vec2 closest_point = get_closest_point_on_segment(bola.pos, 
                                                      bar.start_point_meters, 
                                                      bar.end_point_meters);

    float rad = bar.radius_meters / 2.0f;

    Ball collision_ball(closest_point.x, 
                        closest_point.y, 
                        -bola.vel.x, 
                        -bola.vel.y, 
                        rad, 
                        bola.mass,
                        BLUE);

    // collision_ball.draw();
    handle_ball_collision(collision_ball, bola, 0.707f);
}

float map_pixel_to_meters_x(int pos_x)
{
    return (static_cast<float>(pos_x / SIM_SCALE));
}

float map_pixel_to_meters_y(int pos_y)
{
    // isso aqui tá meio estranho mas tá funcionando, ver melhor outra hora
    return ( - static_cast<float>((pos_y - SCREEN_HEIGHT) / SIM_SCALE));
}

int map_meters_to_pixel_x(float pos_x)
{
    return (static_cast<int>(pos_x * SIM_SCALE));
}

int map_meters_to_pixel_y(float pos_y)
{
    return (static_cast<int>(SCREEN_HEIGHT - (pos_y * SIM_SCALE)));
}
