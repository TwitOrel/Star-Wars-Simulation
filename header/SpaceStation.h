//
// Created by Orel on 21/04/2024.
//

#ifndef EX3_SPACESTATION_H
#define EX3_SPACESTATION_H

#include <string>
#include "Vector.h"
#include "Object.h"

using namespace std;

class SpaceStation : public Object {
private:
    int contain;
    int produces;

public:
    SpaceStation(float x, float y, int count, int producing, const string &name);

    void produce();

    void status() const;

    int transport(int count, int MAX_CARRY);

};


#endif //EX3_SPACESTATION_H
