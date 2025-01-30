//
// Created by Orel on 28/04/2024.
//

#ifndef EX3_DESTROYER_H
#define EX3_DESTROYER_H

#include "SpaceShip.h"
#include "AdmiralFactory.h"
#include "Rocket.h"
#include "Object.h"

class Destroyer : public SpaceShip {
    static const int SPEED = 2;
    static AdmiralFactory pilotFactory;
    shared_ptr<ImperialAgent> pilot;

    pair<Object, bool> destinationTo;
    pair<float, bool> courseTo;
    pair<Vector, bool> positionTo;


public:
    Destroyer(const string &shipName, const string &agentName, float x, float y);

    void destination(Object &site);

    void course(float course);

    void position(float x, float y);

    shared_ptr<ImperialAgent> getAgent() const;

    void status() const;

    void go();

    void stopped();
};


#endif //EX3_DESTROYER_H
