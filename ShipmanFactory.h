//
// Created by Orel on 21/04/2024.
//

#ifndef EX3_SHIPMANFACTORY_H
#define EX3_SHIPMANFACTORY_H

#include <string>
#include <memory>
#include "Shipman.h"

using namespace std;

#include "AgentFactory.h"

class ShipmanFactory : AgentFactory {
public:
    shared_ptr<ImperialAgent> create(const string &name, bool onDuty) const override;

    shared_ptr<ImperialAgent> create(const string &name) const override;
};

#endif //EX3_SHIPMANFACTORY_H