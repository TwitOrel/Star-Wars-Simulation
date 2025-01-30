//
// Created by Orel on 26/04/2024.
//

#include <sstream>
#include "Bomber.h"
#include "Model.h"


Bomber::Bomber(const string &shipName, const string &agentName, const Vector &startLocation) :
        SpaceShip(shipName, startLocation, SPEED),
        sites(map<shared_ptr<Object>, bool>()),
        startedPatrol(this->location, false),
        movingTo(*this, false),
        destinationTo(*this, false),
        courseTo(-1, false),
        positionTo(Vector(), false) {
    Model &m = Model::getInstance();
    if (m.ExistAgent(agentName) == Model::NOT_ON_DUTY) {
        pilot = m.getInDuty(agentName);
        if (pilot->getRank() != "Commander") {
            throw invalid_argument("\nError, Bomber C'tor: Bomber cannot allow agent who's not commander \n");
        }
    } else {
        pilot = (pilotFactory.create(agentName, false));
    }

    // locate the sites
    for (const auto &it: m.getFortress()) {
        sites.emplace(it, false);
    }
    for (const auto &it: m.getSpaceStations()) {
        sites.emplace(it, false);
    }
}

void Bomber::destination(Object &site) {
    setPosition(Moving);
    destinationTo = {site, true};
    courseTo.second = false;
    positionTo.second = false;
    movingTo.second = false;
}

void Bomber::course(float course) {
    setPosition(Moving);
    destinationTo.second = false;
    courseTo = {course, true};
    positionTo.second = false;
    movingTo.second = false;
}

void Bomber::position(float x, float y) {
    setPosition(Moving);
    destinationTo.second = false;
    courseTo.second = false;
    positionTo = {Vector(x, y), true};
    movingTo.second = false;
}

void Bomber::status() const {
    cout << "bomber " << getName() << " at (" << getLocation().getX() << ", " << getLocation().getY() << ")";

    if (getPosition() == Moving) {
        cout << ", " << "Heading ";
        if (movingTo.second) {
            cout << "to " << movingTo.first.getName();
        }
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

void Bomber::go() {
    if (getPosition() == Stopped) {
        return;
    }
    if (movingTo.second) {
        this->location.getCloseTo(movingTo.first.getLocation(), speed);
        if (location == movingTo.first.getLocation()) {
            nextDestination();
        }
    }
    if (destinationTo.second) {
        this->location.getCloseTo(destinationTo.first.getLocation(), speed);
        if (location == destinationTo.first.getLocation()) {
            destinationTo.second = false;
            nextDestination();
        }
    }
    if (courseTo.second) {
        this->location.getCloseTo(courseTo.first, speed);
    }

    if (positionTo.second) {
        this->location.getCloseTo(positionTo.first, speed);
        if (location == positionTo.first) {
            positionTo.second = false;
            nextDestination();
        }
    }

    if (startedPatrol.second) {
        location.getCloseTo(startedPatrol.first, speed);
        if (location == startedPatrol.first) {
            startedPatrol.second = false;
            for (auto &it: sites) {
                it.second = false;
            }
            nextDestination();
        }
    }
}

void Bomber::nextDestination() {
    if (getPosition() == Stopped) {
        return;
    }
    map<shared_ptr<Object>, float> distances;
    pair<shared_ptr<Object>, float> tmp;
    unsigned int forTmp = 0;
    for (auto &site: sites) {
        if (!site.second) {
            distances[site.first] = location.distance(site.first->getLocation());
            // used only to take on for see who the closer
            if (forTmp == 0) {
                forTmp++;
                tmp = pair<shared_ptr<Object>, float>(site.first, location.distance(site.first->getLocation()));
            }

        }
    }
    // check if finish patrol then move to the started point
    if (distances.empty()) {
        movingTo.second = false;
        startedPatrol.second = true;
    }
        // if not finish patrol looking for the closer station
    else {
        for (auto &site: distances) {
            if (site.second < tmp.second) {
                tmp = site;
            }
        }
        movingTo.second = true;
        movingTo.first = *(tmp.first);
    }
}

void Bomber::stopped() {
    setPosition(Stopped);
    movingTo.second = startedPatrol.second = destinationTo.second = courseTo.second = positionTo.second = false;
}

shared_ptr<ImperialAgent> Bomber::getAgent() const {
    return this->pilot;
}

CommanderFactory Bomber::pilotFactory = CommanderFactory();




