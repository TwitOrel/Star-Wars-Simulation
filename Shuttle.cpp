//
// Created by Orel on 24/04/2024.
//

#include <sstream>
#include "Shuttle.h"
#include "Model.h"

using namespace std;

Shuttle::Shuttle(const string &shipName, const string &agentName, float x, float y) :
        SpaceShip(shipName, x, y, SPEED),
        destination(make_shared<Object>()),
        countCrystals(0),
        powerLife(START_POWER_LIFE){
    Model &m = Model::getInstance();
    if (m.ExistAgent(agentName) == Model::NOT_ON_DUTY) {
        pilot = m.getInDuty(agentName);
        if (pilot->getRank() != "Shipman") {
            throw invalid_argument("\nshuttle cannot allow agent who's not shipman");
        }
    } else {
        pilot = (pilotFactory.create(agentName, false));
    }
}


shared_ptr<ImperialAgent> Shuttle::getAgent() const {
    return this->pilot;
}

void Shuttle::start_supply(shared_ptr<SpaceStation> &station, shared_ptr<FortressStar> &target) {
    this->position = Moving;
    this->commands.emplace(station, target);
    if (commands.size() == 1) {
        destination = commands.front().first;
    }
}

void Shuttle::stopped() {
    setPosition(Stopped);
    while (!(this->commands.empty())) {
        this->commands.pop();
    }
    destination = nullptr;
}
void Shuttle::status() const {
    cout << "shuttle " << getName() << " at (" << getLocation().getX() << ", " << getLocation().getY()
        << "), agent name " << this->getAgent()->getName() << " ";
    spaceShipPosition state = getPosition();

    if (state == Dead) {
        cout << ", position: Dead";
        return;
    }

    if (state == Moving) {
        cout << "Heading to " << this->destination->getName();
    }
    cout << ", speed " << getSpeed() * 1000 << "km/h," << " contain " << countCrystals << " crystals, Strength:  "<< powerLife << endl;
}

bool Shuttle::dealArrival() {
    if (commands.front().first->getLocation() == this->location) {
        countCrystals = this->commands.front().first->transport(countCrystals, MAX_CARRY_ITEMS);
        destination = commands.front().second;
        return false;
    }
    if (commands.front().second->getLocation() == this->location && commands.front().second == destination) {
        if (powerLife < MAX_POWER_LIFE) {
            powerLife++;
        }
        this->commands.front().second->transport(countCrystals);
        countCrystals = 0;
        commands.pop();
        if (commands.empty()) {
            this->position = Docked;
            destination = nullptr;
        } else {
            this->destination = commands.front().first;
        }
        return true;
    }
    return false;
}

void Shuttle::go() {
    if (getPosition() == Dead) {
        return;
    }
    if ((getPosition() == Moving) && (!dealArrival())) {
        this->location.getCloseTo(destination->getLocation(), this->speed);
    }
}

void Shuttle::gotRobbed(bool canRobbed) {
    if (canRobbed) {
        stopped();
        this->countCrystals = 0;
        this->powerLife--;
        if (powerLife == 0) {
            setPosition(Dead);
        }
    }
    this->powerLife--;
    if (powerLife == 0) {
        setPosition(Dead);
    }
}

int Shuttle::getPowerLife() const {
    return this->powerLife;
}

ShipmanFactory Shuttle::pilotFactory = ShipmanFactory();