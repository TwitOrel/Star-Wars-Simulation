//
// Created by Orel on 21/04/2024.
//

#include "../header/SpaceShip.h"


SpaceShip::SpaceShip(const string &name, float x, float y, float speed) :
        Object(name, x, y),
        speed(speed),
        position(Stopped) {}

SpaceShip::SpaceShip(const string &name, const Vector &location, float speed) :
        Object(name, location.getX(), location.getY()),
        speed(speed),
        position(Stopped) {}

void SpaceShip::setPosition(const spaceShipPosition &pos) {
    this->position = pos;
}

float SpaceShip::getSpeed() const {
    return speed;
}

const spaceShipPosition &SpaceShip::getPosition() const {
    return position;
}
