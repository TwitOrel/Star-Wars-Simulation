//
// Created by Orel on 28/04/2024.
//

#ifndef EX3_OBJECT_H
#define EX3_OBJECT_H

#include "string"
#include "Vector.h"

using namespace std;

class Object {
protected:
    string name;
    Vector location;

public:
    Object() = default;

    virtual ~Object() = default;

    Object(const string &name, float x, float y);

    void setLocation(const Vector &v);

    const Vector &getLocation() const;

    string getName() const;

    // used for the show
    string getIcon() const;
};


#endif //EX3_OBJECT_H
