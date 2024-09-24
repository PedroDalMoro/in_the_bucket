#include "vector_2.hpp"

// funções privadas

void Vec2::_copy(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Vec2::_scalar(float scalar)
{
    this->x *= scalar;
    this->y *= scalar;
}

void Vec2::_add(float x, float y)
{
    this->x += x;
    this->y += y;
}

void Vec2::_subtract(float x, float y)
{
    this->x -= x;
    this->y -= y;
}

// construtores

Vec2::Vec2(float x, float y)
{
    _copy(x, y);
}

Vec2::Vec2(const Vec2& other) : x(other.x), y(other.y)
{
    // esse é o construtor de cópia, pra evitar os warnings na hora de criar os objetos com = na frente
}

Vec2::~Vec2()
{
}

// funções públicas

void Vec2::operator = (Vec2 item)
{
    _copy(item.x, item.y);
}

void Vec2::operator *= (float scalar)
{
    _scalar(scalar);
}

void Vec2::operator += (Vec2 item)
{
    _add(item.x, item.y);
}

void Vec2::operator -= (Vec2 item)
{
    _subtract(item.x, item.y);
}

void Vec2::set(float x, float y)
{
    _copy(x, y);
}

void Vec2::copy(Vec2 other)
{
    _copy(other.x, other.y);
}

void Vec2::scalar(float scalar)
{
    _scalar(scalar);
}

void Vec2::add(float x, float y)
{
    _add(x, y);
}

void Vec2::add(Vec2 other)
{
    _add(other.x, other.y);
}

void Vec2::subtract(float x, float y)
{
    _subtract(x, y);
}

void Vec2::subtract(Vec2 other)
{
    _subtract(other.x, other.y);
}

float Vec2::getLength()
{
    return (std::sqrt(std::pow(this->x, 2.0f) + std::pow(this->y, 2.0f)));
}

Vec2 Vec2::getNormalized()
{
    Vec2 ret = { x = this->x, y = this->y };
    float length = this->getLength();

    ret.x /= length;
    ret.y /= length;

    return (ret);
}

float Vec2::dotProduct(Vec2 other)
{
    return ((this->x * other.x) + (this->y * other.y));
}

Vec2 Vec2::getVectorSubtraction(Vec2 left, Vec2 right)
{
    Vec2 ret; 

    ret.copy(left);
    ret.subtract(right);

    return ret; 
}

Vec2 Vec2::getVectorAddition(Vec2 left, Vec2 right)
{
    Vec2 ret; 

    ret.copy(left);
    ret.add(right);

    return ret; 
}

Vec2 Vec2::getVectorScaled(Vec2 vector, float scalar)
{
    Vec2 ret; 

    ret.copy(vector);
    ret.scalar(scalar);

    return ret; 
}
