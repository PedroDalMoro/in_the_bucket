#include "bola.hpp"

Bola::Bola(int pos_x, int pos_y, int rad)
{
    _pos.x = static_cast<float>(pos_x);
    _pos.y = static_cast<float>(pos_y);
    _vel.x = 10.0f;
    _vel.y = 10.0f;
    _rad = rad;
    _amort = 0.5;
}

Bola::~Bola()
{
}

void Bola::update()
{
    // float dt = 1.0f / static_cast<float>(FPS_TARGET);
    float dt = GetFrameTime();

    // std::string coisas;
    // coisas = std::to_string(dt);
    // DrawText(coisas.c_str(), 100, 100, 50,  WHITE);

    float sdt = dt / 5.0f;
    for (size_t i = 0; i < 5; i++)
    {
        _vel.y += 150.0f * sdt;
        _pos.y += _vel.y * sdt;

        _vel.x += 50.0f * sdt;
        _pos.x += _vel.x * sdt;
    }

    // _vel.y += 150.0f * dt;
    // _pos.y += _vel.y * dt;

    // _vel.x += 50.0f * dt;
    // _pos.x += _vel.x * dt;

    if(_pos.y >= SCREEN_HEIGHT)
    {
        _vel.y *= -1.0f;
    }

    if(_pos.x >= SCREEN_WIDTH || _pos.x <= 0)
    {
        _vel.x *= -1.0f;
    }
}

void Bola::draw()
{
    DrawCircle(static_cast<int>(_pos.x), 
                static_cast<int>(_pos.y), 
                _rad, 
                WHITE);
}

