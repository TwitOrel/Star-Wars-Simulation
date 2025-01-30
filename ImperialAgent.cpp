//
// Created by Orel on 21/04/2024.
//

#include <iostream>
#include <sstream>
#include "ImperialAgent.h"

using namespace std;

ImperialAgent::ImperialAgent(string name, string rank, bool status) : rank(std::move(rank)), onDuty(status) {
    if (name.length() > 16) {
        stringstream s;
        s << "\nError in ImperialAgent C'tor: invalid name length cant be longer then 16, " << name << endl;
        throw invalid_argument(s.str());
    }
    this->name = std::move(name);
}

string ImperialAgent::getName() const {
    return this->name;
}

string ImperialAgent::getRank() const {
    return this->rank;
}

bool ImperialAgent::operator==(const ImperialAgent &i) const {
    return this->name == i.name;
}

bool ImperialAgent::isOnDuty() const {
    return this->onDuty;
}

void ImperialAgent::setDuty() {
    this->onDuty = true;
}
