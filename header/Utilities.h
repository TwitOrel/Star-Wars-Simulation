//
// Created by Orel on 06/05/2024.
//

#ifndef EX3_UTILITIES_H
#define EX3_UTILITIES_H

#include <string>
#include <map>

using namespace std;

// return map for the Commands for the switch case to handle user asks
void simulateCommands(map<string, int> &map);

// return map for the shipCommands for the switch case
void shipCommands(map<string, int> &map);

string removeFirstWord(const std::string &input);

enum spaceShipPosition {
    Stopped, Docked, Dead, Moving
};


#endif //EX3_UTILITIES_H

