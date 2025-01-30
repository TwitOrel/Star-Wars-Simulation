//
// Created by Orel on 21/04/2024.
//

#ifndef EX3_VECTOR_H
#define EX3_VECTOR_H

#include "Utilities.h"

// this vector using for 2 dim
class Vector {
private:
    float x;
    float y;
public:
    explicit Vector(float x = 0, float y = 0);

    Vector(const Vector &o) = default;

    Vector(Vector &&o) noexcept;

    bool operator==(const Vector &v) const;

    Vector &operator=(const Vector &o) = default;

    Vector &operator=(Vector &&o) noexcept;

    Vector &operator+=(const Vector &v);

    Vector &operator-=(const Vector &v);

    Vector operator+(const Vector &v) const;

    Vector operator-(const Vector &v) const;

    Vector operator/(int v) const;

    Vector &operator*(float t);

    float getX() const;

    float getY() const;

    void setX(float x);

    void setY(float y);

    void setXY(float x, float y);

    float innerMultiply(const Vector &v) const;

    Vector normalized() const;

    float distance(const Vector &v) const;

    // getting closer to vector v (if the distance smaller than the speed, then reach to destination)
    Vector &getCloseTo(const Vector &v, float speed);

    Vector &getCloseTo(float course, float speed);

};

#endif //EX3_VECTOR_H
