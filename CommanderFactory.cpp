//
// Created by Orel on 22/04/2024.
//

#include "CommanderFactory.h"

shared_ptr<ImperialAgent> CommanderFactory::create(const string &name, bool onDuty) const {
    return make_shared<Commander>(name, onDuty);
}

shared_ptr<ImperialAgent> CommanderFactory::create(const string &name) const {
    return create(name, false);
}
