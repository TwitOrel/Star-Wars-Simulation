//
// Created by Orel on 21/04/2024.
//

#ifndef EX3_CONTROLLER_H
#define EX3_CONTROLLER_H

#include "View.h"
#include "Model.h"

using namespace std;

class Controller {
private:
    int time;
    View view;
    Model &model;

public:
    explicit Controller();

    void run(int argc, char *argv[]);
};

#endif //EX3_CONTROLLER_H