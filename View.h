//
// Created by Orel on 21/04/2024.
//

#ifndef EX3_VIEW_H
#define EX3_VIEW_H

#include "Object.h"
#include "vector"
#include "Vector.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <memory>

using namespace std;

class View {
private:
    int sizeOf;
    float scale;
    Vector headOfView;

    // check if object location in the current board area if yes adding
    void canAddToBoard(const shared_ptr<Object> &v, vector<vector<string>> &m) const;

    // iterate each size and ship and using canAddToBoard func
    void addObjectsToBoard(vector<vector<string>> &m) const;

    // print the board with the axis
    void printBoard(vector<vector<string>> &m) const;

public:
    explicit View();

    // commands by the user
    void defaultView();

    void size(stringstream &ss);

    void zoom(stringstream &ss);

    void pan(stringstream &ss);

    void show() const;
};


#endif //EX3_VIEW_H
