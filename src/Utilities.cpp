//
// Created by Orel on 06/05/2024.
//

#include "../header/Utilities.h"

void simulateCommands(map<string, int> &map) {
    map.insert({"default", 1});
    map.insert({"size", 2});
    map.insert({"zoom", 3});
    map.insert({"pan", 4});
    map.insert({"show", 5});
    map.insert({"status", 6});
    map.insert({"go", 7});
    map.insert({"create", 8});
    map.insert({"exit", 9});
    map.insert({"man", 10});

}

void shipCommands(map<string, int> &map) {
    map.insert({"course", 1});
    map.insert({"position", 2});
    map.insert({"destination", 3});
    map.insert({"attack", 4});
    map.insert({"shoot", 5});
    map.insert({"start_supply", 6});
    map.insert({"stop", 7});
    map.insert({"status", 8});

}

string removeFirstWord(const std::string &input) {
    size_t pos = input.find(' ');
    if (pos != string::npos) {
        return input.substr(pos + 1);
    }
    return ""; // or return input;
}
