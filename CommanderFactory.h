//
// Created by Orel on 22/04/2024.
//

#ifndef EX3_COMMANDERFACTORY_H
#define EX3_COMMANDERFACTORY_H

#include "AgentFactory.h"
#include "Commander.h"

using namespace std;

class CommanderFactory : AgentFactory {
public:
    shared_ptr<ImperialAgent> create(const string &name, bool onDuty) const override;

    shared_ptr<ImperialAgent> create(const string &name) const override;
};


#endif //EX3_COMMANDERFACTORY_H
