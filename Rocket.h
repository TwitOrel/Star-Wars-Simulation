//
// Created by Orel on 02/05/2024.
//

#ifndef EX3_ROCKET_H
#define EX3_ROCKET_H

#include "Vector.h"

class Rocket {
    static constexpr float SPEED = 3;
    Vector location;
    Vector destination;

public:
    Rocket(Vector l, float x, float y);

    // check if the rocked arrived to his destination
    bool arrived() const;

    // getting close to his destination
    void go();

    Vector getLocation() const;
};


#endif //EX3_ROCKET_H
