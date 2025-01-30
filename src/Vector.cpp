//
// Created by Orel on 21/04/2024.
//

#include "../header/Vector.h"

#include <cmath>
#include <algorithm>

Vector::Vector(float x, float y) : x(x), y(y) {}

Vector::Vector(Vector &&o) noexcept {
    this->x = o.x;
    this->y = o.y;
    o.x = 0;
    o.y = 0;
}

Vector &Vector::operator=(Vector &&o) noexcept {
    this->x = o.x;
    this->y = o.y;
    o.x = 0;
    o.y = 0;
    return *this;
}

Vector &Vector::operator+=(const Vector &v) {
    this->x += v.x;
    this->y += v.y;
    return *this;
}

Vector &Vector::operator-=(const Vector &v) {
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}

Vector Vector::operator+(const Vector &v) const {
    return Vector(this->x + v.x, this->y + v.y);
}

Vector Vector::operator-(const Vector &v) const {
    return Vector(this->x - v.x, this->y - v.y);
}

float Vector::getX() const {
    return this->x;
}

float Vector::getY() const {
    return this->y;
}

void Vector::setX(float newX) {
    this->x = newX;
}

void Vector::setY(float newY) {
    this->y = newY;
}

void Vector::setXY(float newX, float newY) {
    this->x = newX;
    this->y = newY;
}

float Vector::innerMultiply(const Vector &v) const {
    return (this->x * v.x + this->y * v.y);
}

Vector Vector::normalized() const {
    float denominator = 0;
    denominator += (innerMultiply(*this));
    denominator = sqrt(denominator);
    return Vector(this->x / denominator, this->y / denominator);
}

bool Vector::operator==(const Vector &v) const {
    return ((this->x == v.x) && (this->y == v.y));
}

Vector &Vector::operator*(float t) {
    this->y *= t;
    this->x *= t;
    return *this;
}

float Vector::distance(const Vector &v) const {
    float dx = this->x - v.x;
    float dy = this->y - v.y;
    return std::sqrt(dx * dx + dy * dy);
}

Vector Vector::operator/(int v) const {
    Vector ret = *this;
    ret.x /= float(v);
    ret.y /= float(v);
    return ret;
}

Vector &Vector::getCloseTo(const Vector &v, float speed) {
    if (v == *this) {
        return *this;
    }
    Vector dif = v - *this;
    Vector norm = dif.normalized();

    float distance = std::min(this->distance(v), speed);
    *this += norm * distance;

    return *this;
}

Vector &Vector::getCloseTo(float course, float speed) {
    course = float(fmod(course, 360));
    course *= M_PI / 180;

    float delta_x = std::sin(course) * speed;
    float delta_y = std::cos(course) * speed;

    this->x += delta_x;
    this->y += delta_y;

    return *this;
}