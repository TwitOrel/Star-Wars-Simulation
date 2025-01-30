//
// Created by Orel on 21/04/2024.
//

#include <iostream>
#include "../header/FortressStar.h"

FortressStar::FortressStar(float x, float y, const string &name, int count) :
        Object(name, x, y),
        contain(count) {}

void FortressStar::transport(int count) {
    this->contain += count;
}

void FortressStar::status() const {
    cout << "fortress " << getName() << " at position (" << getLocation().getX() << ", " << getLocation().getY()
        << "), Inventory: " << this->contain << endl;
}



