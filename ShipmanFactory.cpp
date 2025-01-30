//
// Created by Orel on 21/04/2024.
//

#include "ShipmanFactory.h"

shared_ptr<ImperialAgent> ShipmanFactory::create(const string &name, bool onDuty) const {
    return make_shared<Shipman>(name, onDuty);
}

shared_ptr<ImperialAgent> ShipmanFactory::create(const string &name) const {
    return create(name, false);
}
