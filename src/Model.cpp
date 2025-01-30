//
// Created by Orel on 21/04/2024.
//

#include <fstream>
#include <sstream>
#include <algorithm>
#include "../header/Model.h"

Model::Model() {
    fortress.push_back(make_shared<FortressStar>(40, 10, "DS", 100000));
}

Model &Model::getInstance() {
    if(!instance){
        instance = std::shared_ptr<Model>(new Model());
    }
    return *instance;
}

const vector<shared_ptr<FortressStar>> &Model::getFortress() const {
    return this->fortress;
}

const vector<shared_ptr<SpaceStation>> &Model::getSpaceStations() const {
    return this->spaceStations;
}

const vector<shared_ptr<Falcon>> &Model::getFalcons() const {
    return this->falcons;
}

const vector<shared_ptr<Bomber>> &Model::getBombers() const {
   return this->bombers;
}

const vector<shared_ptr<Shuttle>> &Model::getShuttles() const {
    return this->shuttles;
}

const vector<shared_ptr<Destroyer>> &Model::getDestroyers() const {
    return this->destroyers;
}

// read the file and adding the sites before starting run
void Model::initConfig(int argc, char **argv) {
    // check if you have 2 files
    if (argc != 2){
        throw invalid_argument(string("\nERROR: ") + argv[0] + " program can run with one file only! \n");
    }
    try {
        ifstream inputFile(argv[1]);
        if (!inputFile){
            throw std::runtime_error("\nError: Could not open the file. \n");
        }
        string line;
        // read line by line and init as needed
        while (getline(inputFile, line)){
            istringstream iss(line);
            string token;
            vector<string> tokens;

            while (getline(iss, token, ',')){
                tokens.push_back(token);
            }
            // stations
            if (tokens.size() == 6 && tokens[0] == "station"){
                string type = tokens[0];
                string name = tokens[1];
                string xs = tokens[2];
                string ys = tokens[3];
                string crystals = tokens[4];
                string producing = tokens[5];

                size_t pos1 = xs.find('(');
                size_t pos2 = xs.find(')');

                double x = stod(xs.substr(pos1 + 1, xs.length()));
                double y = stod(ys.substr(1, pos2 - 1));
                name = name.substr(1);
                int crystalsCount = stoi(crystals);
                int producingCount = stoi(producing);

                spaceStations.push_back(make_shared<SpaceStation>(x,y,crystalsCount, producingCount, name));
            }
            // fortress
            else if(tokens.size() == 5 && tokens[0] == "fortress"){
                string type = tokens[0];
                string name = tokens[1];
                string xs = tokens[2];
                string ys = tokens[3];
                string crystals = tokens[4];

                size_t pos1 = xs.find('(');
                size_t pos2 = xs.find(')');


                double x = stod(xs.substr(pos1 + 1, xs.length()));
                double y = stod(ys.substr(1, pos2 - 1));
                name = name.substr(1);
                int crystalsCount = stoi(crystals);
                fortress.push_back(make_shared<FortressStar>(x, y, name, crystalsCount));
            }
            // something wrong with arguments
            else{
                throw invalid_argument("\nError: wrong arguments for init sites \n");
            }
        }
    }
    catch (const exception& e){
        cerr << "\nException caught, Model, initConfig: " << e.what() << endl;
        exit(-1);
    }
}

// creating what the user ask (agent\spaceShip)
void Model::create(stringstream &ss) {
    stringstream command(removeFirstWord(ss.str()));
    string token;
    vector<string> tokens;
    string type, name, nameSite, nameAgent, xs, ys;
    float x, y;

    while (getline(command, token, ' ')){
        tokens.push_back(token);
    }

    switch (tokens.size()) {
        case 2:               // Agent
            type = tokens[0];
            name = tokens[1];
            createAgent(type, name);
            break;
                            // spaceShip
        case 3:
            if (tokens[0] == "falcon"){
                name = tokens[1];
                nameSite = tokens[2];
                createFalcon(name,nameSite);
            }
            else{
                throw invalid_argument("\ncant createShip with those arguments \n");
            }
            break;
        case 4:
            if (tokens[0] != "falcon") {
                type = tokens[0];
                name = tokens[1];
                nameAgent = tokens[2];
                nameSite = tokens[3];
                if (ExistAgent(nameAgent) == DUTY) {
                    throw invalid_argument("\nthis agent is on duty already \n");
                }
                if (ExistAgent(nameAgent) == NOT_ON_DUTY) {
                    getInDuty(nameAgent);
                }
                createShip(type, name, nameAgent, nameSite);
            }
            else{            // falcon
                name = tokens[1];
                xs = tokens[2];
                ys = tokens[3];

                size_t pos1 = xs.find('(');
                size_t pos2 = xs.find(',');
                size_t pos3 = xs.find(')');

                x = stof(xs.substr(pos1 + 1, pos2));
                y = stof(ys.substr(0, pos3));

                createFalcon(name, x ,y);
            }
            break;
        case 5:
            if (tokens[4] == "falcon"){
                throw invalid_argument("\ncant createShip with those arguments \n");
            }
            else{
                type = tokens[0];
                name = tokens[1];
                nameAgent = tokens[2];
                xs = tokens[3];
                ys = tokens[4];

                size_t pos1 = xs.find('(');
                size_t pos2 = xs.find(',');
                size_t pos3 = xs.find(')');

                x = stof(xs.substr(pos1 + 1, pos2));
                y = stof(ys.substr(0, pos3));

                createShip(type,name,nameAgent,x ,y);
            }
            break;
        default:
            throw invalid_argument("\ncant createShip with those arguments \n");
    }
}

void Model::status() const {
    for (const auto & it: fortress){
       it->status();
    }
    for (const auto & it: spaceStations){
        it->status();
    }
    for (const auto & it: destroyers){
        it->status();
    }
    for (const auto & it: bombers){
        it->status();
    }
    for (const auto & it: shuttles){
        it->status();
    }
    for (const auto & it: falcons){
        it->status();
    }
    cout << endl;
}
void Model::man() {
    cout << "here some use commands for space:" << endl;
    cout << "go" << endl;
    cout << "status" << endl;
    cout << "<Icon> course <Degree>" << endl;
    cout << "create <Ship (falcon)> <Name> (X, Y)" << endl;
    cout << "<Name> course <Degree> <Speed> (for falcon)" << endl;
    cout << "<Icon> <Command(start_supply, destination...)> <SpaceStation>" << endl;
    cout << "create <Imperial Agent (admiral, commander, midshipman)> <Name>" << endl;
    cout << "create <Ship (shuttle, bomber, destroyer)> <Icon> <Name> (X, Y)" << endl;

    cout << "\nhere some use commands for view:" << endl;
    cout << "show" << endl;
    cout << "default" << endl;
    cout << "pan <X Y>" << endl;
    cout << "size <int>" << endl;
    cout << "zoom <int>" << endl;
}


void Model::go() {
    for (const auto & station : spaceStations){
        station->produce();
    }

    for (const auto & falcon : falcons){
        if (falcon->getPosition() != Dead){
            falcon->go();
        }
    }
    for (const auto & bomber : bombers){
        bomber->go();
        }
    for (const auto & destroyer : destroyers){
        destroyer->go();
    }
    for (const auto & shuttle : shuttles){
        if (shuttle->getPosition() != Dead){
            shuttle->go();
        }
    }

    // after moving all ships, moving rockets and bomb them while arrived destination
    for (auto rocketIt = rockets.begin(); rocketIt != rockets.end();){
        auto& rocket = *rocketIt;
        rocket->go();
        if (rocket->arrived()){
            for (auto & falcon : falcons) {
                 if (rocket->getLocation() == falcon->getLocation()){
                    falcon->setPosition(Dead);
                }
            }
            rocketIt = rockets.erase(rocketIt);
        } else{
            ++rocketIt;
        }
    }
}

// func for spaceShips commands
void Model::command(stringstream &ss) {
    stringstream error;
    string token;
    vector<string> tokens;
    while (ss >> token){
        tokens.push_back(token);
    }

    if (!existSpaceShip(tokens[0])){
        error << "\nthere is no exist spaceShip " << tokens[0] << endl;
        throw runtime_error(error.str());
    }
    map<string ,int>commands;
    shipCommands(commands);

    switch (commands[tokens[1]]) {
        case 1:     //course
            course(tokens);
            break;
        case 2:     //position
            position(tokens);
            break;
        case 3:     //destination
            destination(tokens);
            break;
        case 4:     //attack
            attack(tokens);
            break;
        case 5:     //shoot
            shoot(tokens);
            break;
        case 6:     //start_supply
            start_supply(tokens);
            break;
        case 7:     //stop
            stop(tokens);
            break;
        case 8:     //stop
             status(tokens);
             break;
        default:
            error << "\nthere is no command " << tokens[1] << " for spaceships" << endl;
            throw runtime_error(error.str());
    }
}

// for spaceShip status
void Model::status(const vector<string> &v) const {
    SpaceShipsType type = existSpaceShip(v[0]);
    if (type == F){
        for (const auto& it: falcons){
            if (it->getName() == v[0]){
                it->status();
                return;
            }
        }
    }
    if (type == S){
        for (const auto& it: shuttles){
            if (it->getName() == v[0]){
                it->status();
                return;
            }
        }
    }
    if (type == B){
        for (const auto& it: bombers){
            if (it->getName() == v[0]){
                it->status();
                return;
            }
        }
    }
    // type is D
    for (const auto& it: destroyers){
        if (it->getName() == v[0]){
            it->status();
            return;
        }
    }
}

void Model::stop(const vector<string> &v) {
    stringstream error;
    SpaceShipsType type = existSpaceShip(v[0]);

    if (type == S){
        for (const auto& it: shuttles){
            if (it->getName() == v[0]){
                if (it->getPosition() == Dead){
                    error << "\nError: " << v[0] << " is dead" << endl;
                    throw runtime_error(error.str());
                }
                it->stopped();
            }
        }
    }
    if (type == F){
        for (const auto& it: falcons){
            if (it->getName() == v[0]){
                if (it->getPosition() == Dead){
                    error << "\nError: " << v[0] << " is dead" << endl;
                    throw runtime_error(error.str());
                }
                it->stopped();
            }
        }
    }
    if (type == B){
        for (const auto& it: bombers){
            if (it->getName() == v[0]){
                it->stopped();
            }
        }
    }
    if (type == D){
        for (const auto& it: bombers){
            if (it->getName() == v[0]){
                it->stopped();
            }
        }
    }
}

void Model::start_supply(const vector<string> &v) {
    stringstream error;
    shared_ptr<Shuttle>s;
    shared_ptr<FortressStar> f;
    shared_ptr<SpaceStation> station;
    for (const auto& it: shuttles){
        if (it->getName() == v[0]){
            if (it->getPosition() == Dead){
                error << "\nError: " << v[0] << " is dead  \n";
                throw runtime_error(error.str());
            }
            s = it;
        }
    }
    for (const auto& it: spaceStations){
        if (it->getName() == v[2]){
            station = it;
            break;
        }
    }
    for (const auto& it: fortress){
        if (it->getName() == v[3]){
            f = it;
            break;
        }
    }
    if (!f || !station){
        error << "\nError with supply command: the sites you named are invalid " << v[2] << " " << v[3] << endl;
        throw runtime_error(error.str());
    }
    s->start_supply(station,f);
}

void Model::shoot(const vector<string> &v) {
    stringstream error;
    shared_ptr<Destroyer> d;
    float x, y;
    bool flag = true;

    size_t pos1 = v[2].find('(');
    size_t pos2 = v[2].find(',');
    size_t pos3 = v[3].find(')');

    x = stof(v[2].substr(pos1 + 1, pos2));
    y = stof(v[3].substr(0, pos3));
    for (const auto& it: destroyers){
        if (it->getName() == v[0]){
            flag = !flag;
            rockets.push_back(make_shared<Rocket>(it->getLocation(), x, y));
        }
    }
    if (flag){      //if you get in so didn't find destroyer
        error << "\nnot exist destroyer " << v[0];
        throw runtime_error(error.str());
    }
}

void Model::attack(const vector<string> &v) {
    stringstream error;
    SpaceShipsType a = existSpaceShip(v[0]);
    SpaceShipsType b = existSpaceShip(v[2]);

    shared_ptr<Falcon> f;
    shared_ptr<Shuttle> s;
    for (const auto & it: falcons){
        if (it->getName() == v[0]){
            f = it;
            break;
        }
    }
    for (const auto & it: shuttles){
        if (it->getName() == v[2]){
            s = it;
            break;
        }
    }
    if (a == F && b == S && f->getName() == v[0] && s->getName() == v[2]){
        f->attack(s);
    } else{
        error << "\nError: invalid inputs for using attack command, " << v[0] << ", " << v[2];
        throw runtime_error(error.str());
    }
}

void Model::destination(const vector<string> &v) {
    stringstream error;
    SpaceShipsType type = existSpaceShip(v[0]);
    if (v.size() != 3 || type == N || type == F || type == S){
        throw runtime_error("\nError, invalid argument with command destination \n");
    } else{
        Object location = locateSiteObject(v[2]);
        if (type == B){
            for (const auto & it: bombers){
                if (it->getName() == v[0]){
                    if (it->getPosition() == Dead){
                        error << "\nError: " <<  v[0] << " is dead";
                        throw runtime_error(error.str());
                    }
                    it->destination(location);
                    return;
                }
            }
        } else {        // type = D for sure
            for (const auto & it: destroyers){
                if (it->getName() == v[0]){
                    if (it->getPosition() == Dead){
                        error << "\nError: " <<  v[0] << " is dead";
                        throw runtime_error(error.str());
                    }
                    it->destination(location);
                    return;
                }
            }
        }
    }
    throw runtime_error("\nError, invalid argument with command destination \n");
}

void Model::position(const vector<string> &v) {
    stringstream error;
    float x, y, speed;
    SpaceShipsType type = existSpaceShip(v[0]);

    size_t pos1 = v[2].find('(');
    size_t pos2 = v[2].find(',');
    size_t pos3 = v[3].find(')');

    x = stof(v[2].substr(pos1 + 1, pos2));
    y = stof(v[3].substr(0, pos3));

    if (v.size() == 5 && type == F){     //falcon (got speed also)
        speed = stof(v[4]);
        for (const auto & it:falcons){
            if (it->getName() == v[0]){
                if (it->getPosition() == Dead){
                    error << "\nError: " <<  v[0] << " is dead";
                    throw runtime_error(error.str());
                }
                it->position(x, y, speed);
                return;
            }
        }
    }
    else if (v.size() == 4 && type != S){
        if (type == B){
            for (const auto & it:bombers){
                if (it->getName() == v[0]){
                    if (it->getPosition() == Dead){
                        error << "\nError: " <<  v[0] << " is dead";
                        throw runtime_error(error.str());
                    }
                    it->position(x, y);
                    return;
                }
            }
        } else if (type == D){
            for (const auto & it:destroyers){
                if (it->getName() == v[0]){
                    if (it->getPosition() == Dead){
                        error << "\nError: " <<  v[0] << " is dead";
                        throw runtime_error(error.str());
                    }
                    it->position(x, y);
                    return;
                }
            }
        }
    }
    // problem with what user wrote
    throw runtime_error("\ninvalid arguments while trying use position command \n");
}

void Model::course(const vector<string> &v) {
    stringstream error;
    float course, speed;
    if (v.size() == 4){     //falcon (got speed also)
        course = stof(v[2]);
        speed = stof(v[3]);
        for (const auto & it: falcons){
            if (it->getName() == v[0]){
                if (it->getPosition() == Dead){
                    error << "\nError: " <<  v[0] << " is dead";
                    throw runtime_error(error.str());
                }
                it->course(course,speed/1000);
                return;
            }
        }
    }
    else if (v.size() == 3){
        course = stof(v[2]);
        for (const auto & it: bombers){
            if (it->getName() == v[0]){
                if (it->getPosition() == Dead){
                    error << "\nError: " <<  v[0] << " is dead";
                    throw runtime_error(error.str());
                }
                it->course(course);
                return;
            }
        }
        for (const auto & it: destroyers){
            if (it->getName() == v[0]){
                if (it->getPosition() == Dead){
                    error << "\nError: " <<  v[0] << " is dead";
                    throw runtime_error(error.str());
                }
                it->course(course);
                return;
            }
        }
        // the user wanted to move shuttle by course
        throw runtime_error("\nshuttle spaceship not supporting command course \n");
    }
    // problem with what user wrote
    throw runtime_error("\ninvalid arguments while trying use course command \n");
}

Model::agentExistAndDuty Model::ExistAgent(const string &name) const {
    for (const auto & it : shipmans){
        if (it->getName() == name){
            if (it->isOnDuty()){    // duty
                return DUTY;
            } else{                 // not on duty
                return NOT_ON_DUTY;
            }
        }
    }
    for (const auto & it : commanders){
        if (it->getName() == name){
            if (it->isOnDuty()){    // duty
                return DUTY;
            } else{                 // not on duty
                return NOT_ON_DUTY;
            }
        }
    }
    for (const auto & it : admirals){
        if (it->getName() == name){
            if (it->isOnDuty()){    // duty
                return DUTY;
            } else{                 // not on duty
                return NOT_ON_DUTY;
            }
        }
    }

    // if we here not exist
    return NOT_EXIST;
}

shared_ptr<ImperialAgent> Model::getInDuty(const string &name) const {
    for (const auto & it : shipmans){
        if (it->getName() == name){
            it->setDuty();
            return it;
        }
    }
    for (const auto & it : commanders){
        if (it->getName() == name){
            it->setDuty();
            return it;

        }
    }
    for (const auto & it : admirals){
        if (it->getName() == name){
            it->setDuty();
            return it;
        }
    }
    // no exist Agent
    stringstream ss;
    ss << "\nError, Model, getInDuty: there is no agent: " << name << endl;
    throw runtime_error(ss.str());
}

void Model::createAgent(const string &typeAgent, const string &nameAgent) {
    stringstream er;
    if (typeAgent == "midshipman"){

        switch (ExistAgent(nameAgent)) {
            // case -1 && 0 are same but when I put then together (-1 | 0) didn't work well
            case 1:
                er << "\nalready exist agent with name: " << nameAgent << endl;
                throw logic_error(er.str());
            case 0:
                er << "\nalready exist agent with name: " << nameAgent << endl;
                throw logic_error(er.str());
            case 2:
                shipmans.push_back(shipmanFactory.create(nameAgent, false));
        }
    }
    else if (typeAgent == "commander"){
        switch (ExistAgent(nameAgent)) {
            // case -1 && 0 are same but when I put then together (-1 | 0) didn't work well
            case 1:
                er << "\nalready exist agent with name: " << nameAgent << endl;
                throw logic_error(er.str());
            case 0:
                er << "\nalready exist agent with name: " << nameAgent << endl;
                throw logic_error(er.str());
            case 2:
                commanders.push_back(commanderFactory.create(nameAgent, false));
        }
    }
    else if (typeAgent == "admiral"){

        switch (ExistAgent(nameAgent)) {
            // case -1 && 0 are same but when I put then together (-1 | 0) didn't work well
            case 1:
                er << "\nalready exist agent with name: " << nameAgent << endl;
                throw logic_error(er.str());
            case 0:
                er << "\nalready exist agent with name: " << nameAgent << endl;
                throw logic_error(er.str());
            case 2:
                admirals.push_back(admiralFactory.create(nameAgent, false));
                break;
        }
    }
    else{
        er << "\nbad type for creating agent: " << typeAgent << endl;
        throw logic_error(er.str());
    }
}

void Model::createFalcon(const string &name, const string &siteName) {
    Vector location = locateSite(siteName);
    falcons.push_back(make_shared<Falcon>(name,location.getX(), location.getY()));
}

void Model::createFalcon(const string &name, float x, float y) {
    falcons.push_back(make_shared<Falcon>(name,x ,y));
}

shared_ptr<ImperialAgent> Model::getAgent(const string &name) const {
    for (const auto & it : shipmans){
        if (it->getName() == name){
            return it;
        }
    }
    for (const auto & it : commanders){
        if (it->getName() == name){
            return it;

        }
    }
    for (const auto & it : admirals){
        if (it->getName() == name){
            return it;
        }
    }
    // no exist Agent
    stringstream ss;
    ss << "\nError, Model, getAgent: there is no agent: " << name << endl;
    throw runtime_error(ss.str());
}

void Model::createShip(const string &type, const string &name, const string &nameAgent, const string &nameSite) {
    stringstream er;
    Vector location = locateSite(nameSite);

    if (type == "shuttle"){
        if (ExistAgent(nameAgent) == NOT_EXIST || getAgent(nameAgent)->getRank() == "Shipman") {
            shared_ptr<Shuttle> s = make_shared<Shuttle>(name, nameAgent, location.getX(), location.getY());
            shuttles.push_back(s);
            shipmans.push_back(s->getAgent());
        } else{
            er << "\nshuttle can get only shipman pilot you gave: " << getAgent(nameAgent)->getRank() << endl;
            throw runtime_error(er.str());
        }
    }
    else if (type == "bomber"){
        if (ExistAgent(nameAgent) == NOT_EXIST || getAgent(nameAgent)->getRank() == "Commander"){
            shared_ptr<Bomber> s = make_shared<Bomber>(name, nameAgent, location);
            bombers.push_back(s);
            commanders.push_back(s->getAgent());
        } else{
            er << "\nbomber can get only commander pilot you gave: " << getAgent(nameAgent)->getRank() << endl;
            throw runtime_error(er.str());
        }
    }
    else if (type == "destroyer"){
        if (ExistAgent(nameAgent) == NOT_EXIST || getAgent(nameAgent)->getRank() == "Admiral"){
            shared_ptr<Destroyer> s = make_shared<Destroyer>(name, nameAgent, location.getX(), location.getY());
            destroyers.push_back(s);
            admirals.push_back(s->getAgent());
        } else{
            er << "\ndestroyer can get only admiral pilot you gave: " << getAgent(nameAgent)->getRank() << endl;
            throw runtime_error(er.str());
        }
    }
    else {
        er << "\nbad type for creating spaceship: " << type << endl;
        throw logic_error(er.str());
    }
}

void Model::createShip(const string &type, const string &name, const string &nameAgent, float x, float y) {
    stringstream er;

    if (type == "shuttle") {
        if (ExistAgent(nameAgent) == NOT_EXIST || getAgent(nameAgent)->getRank() == "Shipman") {
            shared_ptr<Shuttle> s = make_shared<Shuttle>(name, nameAgent, x, y);
            shuttles.push_back(s);
            shipmans.push_back(s->getAgent());
        } else {
            er << "\nshuttle can get only shipman pilot you gave: " << getAgent(nameAgent)->getRank() << endl;
            throw runtime_error(er.str());
        }
    }
    else if (type == "bomber"){
        if (ExistAgent(nameAgent) == NOT_EXIST || getAgent(nameAgent)->getRank() == "Commander"){
            shared_ptr<Bomber> s = make_shared<Bomber>(name, nameAgent, Vector(x,y));
            bombers.push_back(s);
            commanders.push_back(s->getAgent());
        }
        else{
            er << "\nbomber can get only commander pilot you gave: " << getAgent(nameAgent)->getRank() << endl;
            throw runtime_error(er.str());
        }
    }
    else if (type == "destroyer"){
        if (ExistAgent(nameAgent) == NOT_EXIST || getAgent(nameAgent)->getRank() == "Admiral"){
            shared_ptr<Destroyer> s = make_shared<Destroyer>(name, nameAgent, x, y);
            destroyers.push_back(s);
            admirals.push_back(s->getAgent());
        }
        else{
            er << "\ndestroyer can get only admiral pilot you gave: " << getAgent(nameAgent)->getRank() << endl;
            throw runtime_error(er.str());
        }
    }
    else {
        er << "\nbad type for creating spaceship: " << type << endl;
        throw logic_error(er.str());
    }
}

Vector Model::locateSite(const string& name) const {
    Vector ret;
    for (const auto & it: fortress){
        if (it->getName() == name){
            string named = it->getName();
            ret = it->getLocation();
            return ret;
        }
    }
    for (const auto & it: spaceStations){
        string named = it->getName();
        if (it->getName() == name){
            ret = it->getLocation();
            return ret;
        }
    }
    throw runtime_error("\nError in Model locateSite: there is no site with name you ask \n");
}

Object Model::locateSiteObject(const string &name) const {
    Object ret;
    for (const auto & it: fortress){
        if (it->getName() == name){
            ret = *it;
            return ret;
        }
    }
    for (const auto & it: spaceStations){
        if (it->getName() == name){
            ret = *it;
            return ret;
        }
    }
    throw runtime_error("\nError in Model locateSite: there is no site with name you ask \n");
}

Model::SpaceShipsType Model::existSpaceShip(const string &nameShip) const {
    bool a = std::any_of(shuttles.begin(), shuttles.end(), [nameShip](const shared_ptr<Shuttle>& b)->bool{
        return b->getName() == nameShip;
    });
    if (a)return S;
    bool b = std::any_of(bombers.begin(), bombers.end(), [nameShip](const shared_ptr<Bomber>& b)->bool{
        return b->getName() == nameShip;
    });
    if (b)return B;
    bool c = std::any_of(destroyers.begin(), destroyers.end(), [nameShip](const shared_ptr<Destroyer>& b)->bool{
        return b->getName() == nameShip;
    });
    if (c)return D;
    bool d = std::any_of(falcons.begin(), falcons.end(), [nameShip](const shared_ptr<Falcon>& b)->bool{
        return b->getName() == nameShip;
    });
    if (d)return F;
    return N;
}

std::shared_ptr<Model> Model::instance = nullptr;