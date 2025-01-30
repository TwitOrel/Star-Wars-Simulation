//
// Created by Orel on 21/04/2024.
//

#include <iostream>
#include "SpaceStation.h"

SpaceStation::SpaceStation(float x, float y, int count, int producing, const string &name) :
        Object(name, x, y),
        contain(count),
        produces(producing) {}

void SpaceStation::produce() {
    this->contain += produces;
}

int SpaceStation::transport(int count, int MAX_CARRY) {
    int ret = MAX_CARRY - count;
    if (contain >= MAX_CARRY - count) {
        contain -= ret;
        return count + ret;
    } else {
        contain = ret;
        contain = 0;
        return count + ret;
    }
}

void SpaceStation::status() const {
    cout << "station " << getName() << " at position (" << getLocation().getX() << ", " << getLocation().getY()
        << "), Inventory: " << this->contain << endl;
}



