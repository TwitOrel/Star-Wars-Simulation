//
// Created by Orel on 28/04/2024.
//

#include <sstream>
#include "../header/Object.h"

Object::Object(const string &name, float x, float y) : name(name), location(Vector(x, y)) {
    if (name.length() > 16) {
        stringstream s;
        s << "\nError Object C'tor: invalid name length cant be longer then 16, " << name << endl;
        throw invalid_argument(s.str());
    }
}

void Object::setLocation(const Vector &v) {
    location.setX(v.getX());
    location.setY(v.getY());
}

const Vector &Object::getLocation() const {
    return location;
}

string Object::getName() const {
    return name;
}

string Object::getIcon() const {
    stringstream ss;
    if (name.size() == 1) {
        ss << name << " ";
        return ss.str();
    }
    return name.substr(0, 2);
}