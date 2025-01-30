//
// Created by Orel on 21/04/2024.
//

#ifndef EX3_SPACESHIP_H
#define EX3_SPACESHIP_H

#include "Vector.h"
#include <string>
#include "SpaceStation.h"
#include "FortressStar.h"
#include "ShipmanFactory.h"
#include "Commander.h"
#include "Admiral.h"
#include "Object.h"
#include "Utilities.h"

using namespace std;

class SpaceShip : public Object {
protected:
    float speed;
    spaceShipPosition position;


public:
    explicit SpaceShip(const string &name, float x, float y, float speed);

    explicit SpaceShip(const string &name, const Vector &location, float speed);

    ~SpaceShip() override = default;

    float getSpeed() const;

    const spaceShipPosition &getPosition() const;

    void setPosition(const spaceShipPosition &pos);

};


#endif //EX3_SPACESHIP_H
