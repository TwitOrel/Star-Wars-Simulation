//
// Created by Orel on 28/04/2024.
//

#include <sstream>
#include <algorithm>
#include "Falcon.h"
#include "Model.h"

Falcon::Falcon(const string &name, float x, float y) :
        SpaceShip(name, x, y, MAX_SPEED),
        courseTo({0, false}),
        positionTo(Vector(x, y), false),
        attackTo(make_shared<Shuttle>(".", ".", 0, 0), false),
        power(INIT_POWER),
        speed(MAX_SPEED) {}

void Falcon::course(float course, float newSpeed) {
    if (newSpeed > MAX_SPEED || newSpeed <= 0) {
        throw runtime_error("\n speed cant be positive or bigger then max speed \n");
    }
    setPosition(Moving);
    this->speed = newSpeed;
    positionTo.second = false;
    courseTo = {course, true};
}

void Falcon::position(float x, float y, float newSpeed) {
    setPosition(Moving);
    this->speed = newSpeed;
    courseTo.second = false;
    positionTo = {Vector(x, y), true};
}

void Falcon::attack(const shared_ptr<Shuttle> &s) {
    if (((location.distance(s->getLocation()) / 1000) <= 0.1)) {
        attackTo = {s, true};
        courseTo.second = false;
        positionTo.second = false;
    }
}

void Falcon::stopped() {
    setPosition(Stopped);
    speed = MAX_SPEED;
    courseTo.second = positionTo.second = attackTo.second = false;
}

void Falcon::status()const {
    cout << "falcon " << getName() << " at (" << getLocation().getX() << ", " << getLocation().getY() << ")";
    if (getPosition() == Dead) {
        cout << ", position: Dead";
        return;
    }

    if (getPosition() == Moving) {
        cout << ", " << "Heading ";
        if (courseTo.second) {
            cout << "on course " << courseTo.first << " deg";
        }
        if (positionTo.second) {
            cout << "on (" << positionTo.first.getX() << ", " << positionTo.first.getY() << ")";
        }
    }
    cout << ", speed " << getSpeed() * 1000 << "km/h, Strength: " << this->power << endl;
}

bool Falcon::rob() {
    if (attackTo.first->getPowerLife() < power &&
        (location.distance(attackTo.first->getLocation() / 1000) < 0.1) &&
        !bomberAround(attackTo.first->getLocation())
            ) {
        attackTo.first->gotRobbed(true);
        if (power < MAX_POWER) {
            power++;
        }
        return true;
    }
    attackTo.first->gotRobbed();
    return false;

}

void Falcon::go() {
    if (getPosition() == Dead) {
        return;
    }
    if (attackTo.second) {
        if (!rob()) {
            if (--power) {
                setPosition(Dead);
            }
        }
        setLocation(attackTo.first->getLocation());
        stopped();
        return;
    }
    if (getPosition() == Stopped) {
        return;
    }
    if (courseTo.second) {
        this->location.getCloseTo(courseTo.first, speed);
    }
    if (positionTo.second) {
        this->location.getCloseTo(positionTo.first, speed);
        if (location == positionTo.first) {
            positionTo.second = false;
            this->speed = MAX_SPEED;
            setPosition(Docked);
        }
    }
}

bool Falcon::bomberAround(const Vector &v) {
    auto a = Model::getInstance().getBombers();
    return std::any_of(a.begin(), a.end(), [v](const shared_ptr<Bomber> &b) -> bool {
        return v.distance(b->getLocation()) / 1000 < 0.25;
    });
}

