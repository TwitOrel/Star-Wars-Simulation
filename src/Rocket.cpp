//
// Created by Orel on 02/05/2024.
//

#include "../header/Rocket.h"

#include <utility>

Rocket::Rocket(Vector l, float x, float y) : location(std::move(l)), destination(x, y) {}

bool Rocket::arrived() const {
    return location == destination;
}

void Rocket::go() {
    location.getCloseTo(destination, SPEED);
}

Vector Rocket::getLocation() const {
    return this->location;
}
