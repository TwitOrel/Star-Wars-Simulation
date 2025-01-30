//
// Created by Orel on 22/04/2024.
//

#include "../header/AdmiralFactory.h"

shared_ptr<ImperialAgent> AdmiralFactory::create(const string &name, bool onDuty) const {
    return make_shared<Admiral>(name, onDuty);
}

shared_ptr<ImperialAgent> AdmiralFactory::create(const string &name) const {
    return create(name, false);
}
