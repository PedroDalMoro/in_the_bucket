#ifndef VECTOR_2_HPP
#define VECTOR_2_HPP

#include <cmath>

/**
 * @brief Class that handles mathematical operations on vectors (x and y).
 * 
 * TODO: I tested all operations, but if we ever do unit tests, 
 * this class would be a good place to start because all functions have a clear expected result, 
 * without other effects.
 */
class Vec2
{
private:
    void _copy(float x, float y);                    // assigns one vector to another
    void _scalar(float scalar);                      // multiplies the vector by a scalar
    void _add(float x, float y);                     // adds values to the vector
    void _subtract(float x, float y);                // subtracts values from the vector

public:
    float x;
    float y;

    Vec2(float x = 0.0f, float y = 0.0f);
    Vec2(const Vec2& copy);
    ~Vec2();

    // operators to directly handle vectors
    void operator = (Vec2 item);                    // assigns one vector to another
    void operator *= (float scalar);                // multiplies the vector by a scalar
    void operator += (Vec2 item);                   // adds one vector to another
    void operator -= (Vec2 item);                   // subtracts one vector from another (first minus the second)

    // same as operators, but with functions
    void set(float x, float y);                     // assigns values to the vector
    void copy(Vec2 other);                          // assigns one vector to another
    void scalar(float scalar);                      // multiplies the vector by a scalar
    void add(float x, float y);                     // adds values to the vector
    void add(Vec2 other);                           // adds one vector to another
    void subtract(float x, float y);                // subtracts values from the vector
    void subtract(Vec2 other);                      // subtracts one vector from another (this - other)

    // other functions for vector mathematics
    float getLength();                              // returns the length (magnitude) of the vector
    Vec2 getNormalized();                           // returns the normalized vector (divided by the magnitude)
    float dotProduct(Vec2 other);                   // returns the dot product ((vx * ux) + (vy * uy))

    // declared as static to be accessible without the object (Vec2::func() for example)
    static Vec2 getVectorSubtraction(Vec2 left, Vec2 right);
    static Vec2 getVectorAddition(Vec2 left, Vec2 right);
    static Vec2 getVectorScaled(Vec2 vector, float scalar);
};

#endif  // VECTOR_2_HPP