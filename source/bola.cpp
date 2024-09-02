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

void Bola::init(float pos_x_meters, float pos_y_meters, float vel_x_mps, float vel_y_mps, float rad_meters, Color cor)
{
    _pos.x = pos_x_meters;
    _pos.y = pos_y_meters;
    _vel.x = vel_x_mps;
    _vel.y = vel_y_mps;
    _rad = rad_meters;
    _cor = cor;
}

void Bola::update()
{
    float dt = GetFrameTime();

    float sdt = dt / 5.0f;
    for (size_t i = 0; i < 5; i++)
    {
        _vel.y += -9.81f * sdt;
        _pos.y += _vel.y * sdt;

        // _vel.x += 50.0f * sdt;
        _pos.x += _vel.x * sdt;
    }

    if(_pos.y <= 0.0f)
    {
        _vel.y *= -1.0f;
    }

    if(_pos.x >= SIM_WIDTH || _pos.x <= 0)
    {
        _vel.x *= -1.0f;
    }
}

void Bola::draw()
{
    DrawCircle(_map_x(_pos.x), 
                _map_y(_pos.y), 
                _map_rad(_rad), 
                _cor);
}
