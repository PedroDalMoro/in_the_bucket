#include "bola.hpp"

int Bola::_map_x(float pos_x)
{
    return (static_cast<int>(pos_x * SIM_SCALE));
}

int Bola::_map_y(float pos_y)
{
    return (static_cast<int>(SCREEN_HEIGHT - (pos_y * SIM_SCALE)));
}

int Bola::_map_rad(float rad)
{
    return (static_cast<int>(rad * SIM_SCALE));
}

Bola::Bola(float pos_x_meters, float pos_y_meters, float vel_x_mps, float vel_y_mps, float rad_meters, Color cor)
{
    init(pos_x_meters, pos_y_meters, vel_x_mps, vel_y_mps, rad_meters, cor);
}

Bola::Bola()
{
}

Bola::~Bola()
{
}

void Bola::init(float pos_x_meters, float pos_y_meters, float vel_x_mps, float vel_y_mps, float rad_meters, Color color)
{
    pos.x = pos_x_meters;
    pos.y = pos_y_meters;
    vel.x = vel_x_mps;
    vel.y = vel_y_mps;
    rad = rad_meters;
    mass = rad_meters * rad_meters * PI;       // vi um exemplo com isso, e funciona (mas poderia virar algo mais "real" alguma hora)
    cor = color;
}

void Bola::update()
{
    float dt = GetFrameTime();

    float sdt = dt / 5.0f;
    for (size_t i = 0; i < 5; i++)
    {
        vel.y += -9.81f * sdt;
        pos.y += vel.y * sdt;

        // vel.x += 50.0f * sdt;
        pos.x += vel.x * sdt;
    }

    // alterda a comparação pra -1 pra que as bolinhas grudadas fiquem ocultas
    // if((pos.y - rad) <= -1.0f)
    if((pos.y - rad) <= 0.0f)
    {
        vel.y *= -1.0f;
    }

    if((pos.x + rad) >= SIM_WIDTH || (pos.x - rad) <= 0)
    {
        vel.x *= -1.0f;
    }
}

void Bola::draw()
{
    DrawCircle(_map_x(pos.x), 
                _map_y(pos.y), 
                _map_rad(rad), 
                cor);
}
