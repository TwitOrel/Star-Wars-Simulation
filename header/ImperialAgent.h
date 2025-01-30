//
// Created by Orel on 21/04/2024.
//

#ifndef EX3_IMPERIALAGENT_H
#define EX3_IMPERIALAGENT_H

#include <string>

using namespace std;

class ImperialAgent {
private:
    string name;
    string rank;
    bool onDuty;

public:
    explicit ImperialAgent(string name, string rank, bool status = false);

    // check if already on spaceship
    bool isOnDuty() const;

    ~ImperialAgent() = default;


    // by their name
    bool operator==(const ImperialAgent &i) const;

    string getName() const;

    string getRank() const;

    void setDuty();

};


#endif //EX3_IMPERIALAGENT_H
