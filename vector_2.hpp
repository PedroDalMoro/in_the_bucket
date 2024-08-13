#ifndef VECTOR_2_HPP
#define VECTOR_2_HPP

#include <cmath>

/**
 * @brief Classe que lida com as operações matemáticas nos vetores (x e y). 
 * 
 * TODO: testei todas as operações, mas se algum dia a gente fizer as coisas de unit tests, 
 * essa classe seria um lugar bem bom pra começar, porque todas as funções tem um resultado 
 * esperado claro, sem outros efeitos. 
 */
class Vec2
{
private:
    void _copy(float x, float y);                    // atribui um vetor ao outro 
    void _scalar(float scalar);                      // multiplica o vetor por um escalar
    void _add(float x, float y);                     // soma valores ao vetor 
    void _subtract(float x, float y);                // diminui valores do vetor

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

    // mesmo que os operadores, mas com funções
    void set(float x, float y);                     // atribui valores ao vetor
    void copy(Vec2 other);                          // atribui um vetor ao outro 
    void scalar(float scalar);                      // multiplica o vetor por um escalar
    void add(float x, float y);                     // soma valores ao vetor 
    void add(Vec2 other);                           // soma um vetor ao outro 
    void subtract(float x, float y);                // diminui valores do vetor
    void subtract(Vec2 other);                      // diminui um vetor do outro (this - other)

    // outras funções pra matemática de vetores
    float getLength();                              // retorna o tamanho (módulo) do vetor
    Vec2 getNormalized();                           // retorna o vetor normalizado (dividido pelo módulo)
    float dotProduct(Vec2 other);                   // retorna o dot procutd ((vx * ux) + (vy * uy))
};

#endif  // VECTOR_2_HPP