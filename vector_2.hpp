#ifndef VECTOR_2_HPP
#define VECTOR_2_HPP

#include <cmath>

class Vec2
{
private:

public:
    float x;
    float y;

    Vec2(float x = 0.0f, float y = 0.0f);
    ~Vec2();

    // operadores pra lidar direto com os vetores
    void operator = (Vec2 item);                    // atribui um vetor ao outro 
    void operator *= (float scalar);                // multiplica o vetor por um escalar
    void operator += (Vec2 item);                   // soma um vetor ao outro 
    void operator -= (Vec2 item);                   // diminui um vetor do outro (primeiro menos o segundo)

    // funções pra matemática de vetores
    float getLength();                              // retorna o tamanho (módulo) do vetor
    Vec2 getNormalized();                           // retorna o vetor normalizado (dividido pelo módulo)
    float dotProduct(Vec2 other);                   // retorna o dot procutd ((vx * ux) + (vy * uy))

};

Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vec2::~Vec2()
{
}

void Vec2::operator = (Vec2 item)
{
    this->x = item.x;
    this->y = item.y;
}

void Vec2::operator *= (float scalar)
{
    this->x *= scalar;
    this->y *= scalar;
}

void Vec2::operator += (Vec2 item)
{
    this->x += item.x;
    this->y += item.y;
}

void Vec2::operator -= (Vec2 item)
{
    this->x -= item.x;
    this->y -= item.y;
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

#endif  // VECTOR_2_HPP


// COISAS PRA TESTAR USANDO O COMPILADOR ONLINE, APAGAR DEPOIS E TENHO AINDA QUE MUDAR AS COISAS PRO CPP

// // Online C++ compiler to run C++ program online
// #include <iostream>
// #include <cmath>

// using namespace std;

// class Vec2
// {
// private:

// public:
//     float x;
//     float y;

//     Vec2(float x = 0.0f, float y = 0.0f);
//     ~Vec2();

//     // operadores pra lidar direto com os vetores
//     void operator = (Vec2 item);                    // atribui um vetor ao outro 
//     void operator *= (float scalar);                // multiplica o vetor por um escalar
//     void operator += (Vec2 item);                   // soma um vetor ao outro 
//     void operator -= (Vec2 item);                   // diminui um vetor do outro (primeiro menos o segundo)

//     // funções pra matemática de vetores
//     float getLength();                              // retorna o tamanho (módulo) do vetor
//     Vec2 getNormalized();                           // retorna o vetor normalizado (dividido pelo módulo)
//     float dotProduct(Vec2 other);                   // retorna o dot procutd ((vx * ux) + (vy * uy))

// };

// Vec2::Vec2(float x, float y)
// {
//     this->x = x;
//     this->y = y;
// }

// Vec2::~Vec2()
// {
// }

// void Vec2::operator = (Vec2 item)
// {
//     this->x = item.x;
//     this->y = item.y;
// }

// void Vec2::operator *= (float scalar)
// {
//     this->x *= scalar;
//     this->y *= scalar;
// }

// void Vec2::operator += (Vec2 item)
// {
//     this->x += item.x;
//     this->y += item.y;
// }

// void Vec2::operator -= (Vec2 item)
// {
//     this->x -= item.x;
//     this->y -= item.y;
// }

// float Vec2::getLength()
// {
//     return (std::sqrt(std::pow(this->x, 2.0f) + std::pow(this->y, 2.0f)));
// }

// Vec2 Vec2::getNormalized()
// {
//     Vec2 ret = { x = this->x, y = this->y };
//     float length = this->getLength();

//     ret.x /= length;
//     ret.y /= length;

//     return (ret);
// }

// float Vec2::dotProduct(Vec2 other)
// {
//     return ((this->x * other.x) + (this->y * other.y));
// }

// int main() {

//     Vec2 values(12, 24);
//     Vec2 other(100, 200);
    
//     cout << "valores iniciais" << endl;
//     cout << values.x << " - " << values.y << endl;
    
//     values = other;
//     cout << "testando atribuição" << endl;
//     cout << values.x << " - " << values.y << endl;
    
//     values *= 1.5;
//     cout << "testando escalar" << endl;
//     cout << values.x << " - " << values.y << endl;
    
//     values.x = 1.234;
//     values.y = 3.12;
//     cout << "testando módulo" << endl;
//     cout << values.getLength() << endl;

//     values.x = 3;
//     values.y = 4;
//     Vec2 temp = values.getNormalized();
//     cout << "testando normalizado" << endl;
//     cout << temp.x << " - " << temp.y << endl;

//     return 0;
// }