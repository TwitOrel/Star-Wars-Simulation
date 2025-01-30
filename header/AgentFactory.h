//
// Created by Orel on 21/04/2024.
//

#ifndef EX3_AGENTFACTORY_H
#define EX3_AGENTFACTORY_H

#include <string>
#include <memory>
#include "ImperialAgent.h"

using namespace std;


class AgentFactory {
public:
    virtual ~AgentFactory() = default;

    virtual shared_ptr<ImperialAgent> create(const string &name, bool onDuty) const = 0;

    virtual shared_ptr<ImperialAgent> create(const string &name) const = 0;
};


#endif //EX3_AGENTFACTORY_H
