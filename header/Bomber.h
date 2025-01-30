//
// Created by Orel on 26/04/2024.
//

#ifndef EX3_BOMBER_H
#define EX3_BOMBER_H

#include "SpaceShip.h"
#include "CommanderFactory.h"
#include <memory>
#include <map>
#include <iostream>

using namespace std;

class Bomber : public SpaceShip {
private:
    // map will be with vector\spaceships
    map<shared_ptr<Object>, bool> sites;
    static CommanderFactory pilotFactory;
    constexpr static float SPEED = 1;
    shared_ptr<ImperialAgent> pilot;
    pair<Vector, bool> startedPatrol;
    pair<Object, bool> movingTo;
    pair<Object, bool> destinationTo;
    pair<float, bool> courseTo;
    pair<Vector, bool> positionTo;

    void nextDestination();


public:
    Bomber(const string &shipName, const string &agentName, const Vector &startLocation);

    void destination(Object &site);

    void course(float course);

    void position(float x, float y);

    shared_ptr<ImperialAgent> getAgent() const;

    void status() const;

    void go();

    void stopped();

};

#endif //EX3_BOMBER_H
