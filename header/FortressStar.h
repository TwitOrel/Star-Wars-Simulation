//
// Created by Orel on 21/04/2024.
//

#ifndef EX3_FORTRESSSTAR_H
#define EX3_FORTRESSSTAR_H

#include <string>
#include "Object.h"

using namespace std;

class FortressStar : public Object {
private:
    int contain;
public:
    explicit FortressStar(float x, float y, const string &name, int count);

    void transport(int count);

    void status() const;
};


#endif //EX3_FORTRESSSTAR_H
