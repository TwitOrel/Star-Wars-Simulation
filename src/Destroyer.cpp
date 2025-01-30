//
// Created by Orel on 28/04/2024.
//

#include <sstream>
#include "../header/Destroyer.h"
#include "../header/Model.h"

Destroyer::Destroyer(const string &shipName, const string &agentName, float x, float y) :
        SpaceShip(shipName, x, y, SPEED),
        destinationTo(*this, false),
        courseTo(-1, false),
        positionTo(Vector(), false) {
    Model &m = Model::getInstance();
    if (m.ExistAgent(agentName) == Model::NOT_ON_DUTY) {
        pilot = m.getInDuty(agentName);
        if (pilot->getRank() != "Admiral") {
            throw invalid_argument("\nError in Destroyer C'tor: Destroyer cannot allow agent who's not admiral \n");
        }
    } else {
        pilot = (pilotFactory.create(agentName, false));
    }
}

void Destroyer::destination(Object &site) {
    setPosition(Moving);
    destinationTo = {site, true};
    courseTo.second = false;
    positionTo.second = false;
}

void Destroyer::course(float course) {
    setPosition(Moving);
    destinationTo.second = false;
    courseTo = {course, true};
    positionTo.second = false;
}

void Destroyer::position(float x, float y) {
    setPosition(Moving);
    destinationTo.second = false;
    courseTo.second = false;
    positionTo = {Vector(x, y), true};
}

void Destroyer::status() const {
    cout << "destroyer " << getName() << " at (" << getLocation().getX() << ", " << getLocation().getY() << ")";

    if (getPosition() == Moving) {
        cout << ", " << "Heading ";
        if (destinationTo.second) {
            cout << "to " << destinationTo.first.getName();
        }
        if (courseTo.second) {
            cout << "on course " << courseTo.first << " deg";
        }
        if (positionTo.second) {
            cout << "on (" << positionTo.first.getX() << ", " << positionTo.first.getY() << ")";
        }
    }
    cout << ", speed " << getSpeed() * 1000 << "km/h" << endl;
}

void Destroyer::go() {
    if (getPosition() == Stopped) {
        return;
    }
    if (destinationTo.second) {
        this->location.getCloseTo(destinationTo.first.getLocation(), speed);
        if (location == destinationTo.first.getLocation()) {
            destinationTo.second = false;
            setPosition(Docked);
        }
        return;
    }
    if (courseTo.second) {
        this->location.getCloseTo(courseTo.first, speed);
        return;
    }
    if (positionTo.second) {
        this->location.getCloseTo(positionTo.first, speed);
        if (location == positionTo.first) {
            positionTo.second = false;
            setPosition(Docked);
        }
        return;
    }
}

void Destroyer::stopped() {
    setPosition(Stopped);
    destinationTo.second = courseTo.second = positionTo.second = false;
}

AdmiralFactory Destroyer::pilotFactory = AdmiralFactory();

shared_ptr<ImperialAgent> Destroyer::getAgent() const {
    return this->pilot;
}
