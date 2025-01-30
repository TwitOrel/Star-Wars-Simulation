//
// Created by Orel on 21/04/2024.
//

#include <vector>
#include <cmath>
#include <iomanip>
#include "../header/View.h"
#include "../header/Model.h"


using namespace std;

View::View() : sizeOf(25), scale(2), headOfView(0, 0) {}

void View::defaultView() {
    this->headOfView.setXY(0, 0);
    this->scale = 2;
    this->sizeOf = 25;
}

void View::size(stringstream &ss) {
    string token;
    vector<string> tokens;
    while (ss >> token) {
        tokens.push_back(token);
    }
    try {
        int size = stoi(tokens[0]);
        if (tokens.size() != 1) {
            throw runtime_error("\nERROR: New map size need only one int argument size \n");
        }
        if (size < 7) {
            throw runtime_error("\nERROR: New map size is too small. \n");
        }
        if (size > 30) {
            throw runtime_error("\nERROR: New map size is too big. \n");
        }
        this->sizeOf = size;
    }
    catch (invalid_argument &e) {
        throw invalid_argument("\nERROR: Expected an integer. \n");
    }
}

void View::zoom(stringstream &ss) {
    string token;
    vector<string> tokens;
    while (ss >> token) {
        tokens.push_back(token);
    }
    try {
        float newScale = stof(tokens[0]);
        if (tokens.size() != 1) {
            throw runtime_error("\nERROR: New map size need only one int argument size \n");
        }
        if (newScale <= 0) {
            throw runtime_error("\nERROR: New map scale must be positive. \n");
        }
        this->scale = newScale;
    }
    catch (invalid_argument &e) {
        throw invalid_argument("\nERROR: Expected a double. \n");
    }
}

void View::pan(stringstream &ss) {
    string token;
    vector<string> tokens;
    while (ss >> token) {
        tokens.push_back(token);
    }
    if (tokens.size() != 2) {
        throw invalid_argument("\nERROR: New map size need only one int argument size \n");
    }
    this->headOfView = Vector(stof(tokens[0]), stof(tokens[1]));
}

void View::show() const {
    vector<vector<string>> matrix(sizeOf, vector<string>(sizeOf));

    for (int i = 0; i < sizeOf; ++i) {
        for (int j = 0; j < sizeOf; ++j) {
            matrix[i][j] = ". ";
        }
    }
    addObjectsToBoard(matrix);
    printBoard(matrix);
}

void View::printBoard(vector<vector<string>> &m) const {
    cout << "Display size: " << sizeOf << " scale: " << scale << " , origin: (" << headOfView.getX() << ", "
         << headOfView.getY() << ")" << endl;

    for (int i = sizeOf - 1; i >= 0; i--) {
        if (fmod(i, 3) == 0) {

            // used you print Y-axis
            int sh = (sizeOf * int(scale) + int(headOfView.getY()) - (sizeOf - i) * int(scale));
            if (sh < 10 && sh >= 0) { cout << "" << sh << "  "; }
            if (sh < 100 && sh >= 10) { cout << "" << sh << " "; }
            if (sh < 1000 && sh >= 100) { cout << "" << sh << ""; }
            if (sh < 0 && sh >= -9) { cout << "" << sh << " "; }
            if (sh <= -10 && sh >= -100) { cout << "" << sh << ""; }
            if (sh <= -100 && sh >= -1000) { cout << "" << sh; }
        } else {
            cout << "   ";
        }
        // print objects
        for (int j = 0; j < sizeOf; j++) {
            cout << m[i][j];
        }
        cout << endl;
    }
    // used to print X-axis
    int x = int(headOfView.getX());
    while (x < (sizeOf * int(scale) + int(headOfView.getX()))) {
        if (x == int(headOfView.getX())) {
            if (x < 10 && x >= 0) { cout << "   " << x; }
            if (x < 100 && x >= 10) { cout << "  " << x; }
            if (x < 1000 && x >= 100) { cout << " " << x; }
            if (x < 0 && x >= -9) { cout << "  " << x; }
            if (x <= -10 && x >= -100) { cout << " " << x; }
            if (x <= -100 && x >= -1000) { cout << "" << x; }

        } else {
            if (x < 10 && x >= 0) { cout << "     " << x; }
            if (x < 100 && x >= 10) { cout << "    " << x; }
            if (x < 1000 && x >= 100) { cout << "   " << x; }
            if (x < 0 && x >= -9) { cout << "    " << x; }
            if (x <= -10 && x >= -100) { cout << "   " << x; }
            if (x <= -100 && x >= -1000) { cout << "  " << x; }
        }
        x += (3 * int(scale));
    }
    cout << endl << endl;
}

void View::addObjectsToBoard(vector<vector<string>> &matrix) const {
    Model &model = Model::getInstance();
    for (const auto &it: model.getFortress()) {
        canAddToBoard(it, matrix);
    }
    for (const auto &it: model.getSpaceStations()) {
        canAddToBoard(it, matrix);
    }
    for (const auto &it: model.getDestroyers()) {
        canAddToBoard(it, matrix);
    }
    for (const auto &it: model.getFalcons()) {
        canAddToBoard(it, matrix);
    }
    for (const auto &it: model.getShuttles()) {
        canAddToBoard(it, matrix);
    }
    for (const auto &it: model.getBombers()) {
        canAddToBoard(it, matrix);
    }
}

void View::canAddToBoard(const shared_ptr<Object> &v, vector<vector<string>> &m) const {
    int x = int((v->getLocation().getX() - headOfView.getX()) / scale);
    int y = int((v->getLocation().getY() - headOfView.getY()) / scale);
    if ((x >= 0) && (x < sizeOf) && (y >= 0) && (y < sizeOf) && m[y][x] == ". ") {
        m[y][x] = v->getIcon();
    }
}
