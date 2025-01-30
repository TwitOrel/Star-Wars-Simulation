//
// Created by Orel on 22/04/2024.
//

#ifndef EX3_ADMIRALFACTORY_H
#define EX3_ADMIRALFACTORY_H

#include "AgentFactory.h"
#include "Admiral.h"

class AdmiralFactory : AgentFactory {
public:
    shared_ptr<ImperialAgent> create(const string &name, bool onDuty) const override;

    shared_ptr<ImperialAgent> create(const string &name) const override;

};


#endif //EX3_ADMIRALFACTORY_H
