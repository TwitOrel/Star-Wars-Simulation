//
// Created by Orel on 28/04/2024.
//

#ifndef EX3_FALCON_H
#define EX3_FALCON_H

#include "SpaceShip.h"
#include "Shuttle.h"

class Falcon : public SpaceShip {
    const static int MAX_POWER = 20;
    const static int INIT_POWER = 5;
    const static int MAX_SPEED = 3;
    pair<float, bool> courseTo;
    pair<Vector, bool> positionTo;
    pair<shared_ptr<Shuttle>, bool> attackTo;
    int power;
    float speed;

    // robing shuttle
    bool rob();

    // check if there is bomber close to the attack point
    static bool bomberAround(const Vector &v);


public:
    Falcon(const string &name, float x, float y);

    void course(float course, float newSpeed);

    void position(float x, float y, float newSpeed);

    void attack(const shared_ptr<Shuttle> &s);

    void go();

    void status()const;

    void stopped();

};


#endif //EX3_FALCON_H
