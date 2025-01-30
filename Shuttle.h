//
// Created by Orel on 24/04/2024.
//

#ifndef EX3_SHUTTLE_H
#define EX3_SHUTTLE_H

#include "SpaceShip.h"
#include <queue>
#include <tuple>
#include <memory>
#include "Object.h"

using namespace std;

class Falcon;

// not supporting commands (course\position)
class Shuttle : public SpaceShip {
private:
    queue<pair<shared_ptr<SpaceStation>, shared_ptr<FortressStar>>> commands;
    shared_ptr<Object> destination;
    static const int MAX_POWER_LIFE = 20;
    static const int START_POWER_LIFE = 10;
    static const int MAX_CARRY_ITEMS = 5;
    constexpr static const float SPEED = 0.5;
    static ShipmanFactory pilotFactory;
    shared_ptr<ImperialAgent> pilot;
    int countCrystals;
    int powerLife;

    // if arrival to destination do as ask
    bool dealArrival();

public:
    Shuttle(const string &shipName, const string &agentName, float x, float y);

    void go();

    void stopped();

    void status() const;

    int getPowerLife() const;

    // activate when robbed
    void gotRobbed(bool canRobbed = false);

    shared_ptr<ImperialAgent> getAgent() const;

    void start_supply(shared_ptr<SpaceStation> &station, shared_ptr<FortressStar> &target);

};

#endif //EX3_SHUTTLE_H
