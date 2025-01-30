//
// Created by Orel on 21/04/2024.
//

#include <iostream>
#include <sstream>
#include "../header/Controller.h"

using namespace std;

Controller::Controller() : time(0), view(View()), model(Model::getInstance()) {}

void Controller::run(int argc, char **argv) {
    try {
        model.initConfig(argc, argv);
    }
    catch (exception &e) {
        cerr << e.what();
        exit(-1);
    }

    string line;
    map<string, int> map;
    simulateCommands(map);
    cout << "Star Wars Simulation\nfor info use man"<< endl;
    while (true) {
        try {
            cout << "Time " << time << ": Enter command :";
            getline(cin, line);
            stringstream ss(line);

            string command;
            ss >> command;
            switch (map[command]) {
                case 1:     //default
                    this->view.defaultView();
                    break;
                case 2:     // size
                    this->view.size(ss);
                    break;
                case 3:     // zoom
                    this->view.zoom(ss);
                    break;
                case 4:     //pan
                    this->view.pan(ss);
                    break;
                case 5:     //show
                    this->view.show();
                    break;
                case 6:     //status
                    model.status();
                    break;
                case 7:     //go
                    time++;
                    model.go();
                    break;
                case 8:     //createShip
                    model.create(ss);
                    break;
                case 9:     //exit
                    return;
                case 10:    //man
                    model.man();
                    break;
                default:    // spaceship command
                    ss.seekg(0);
                    model.command(ss);
            }
        }
        catch (exception &e) {
            cerr << e.what() << endl;
        }
    }
}
