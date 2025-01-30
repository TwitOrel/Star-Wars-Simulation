//
// Created by Orel on 21/04/2024.
//

#ifndef EX3_MODEL_H
#define EX3_MODEL_H

#include "SpaceShip.h"
#include "Shuttle.h"
#include "Destroyer.h"
#include "SpaceStation.h"
#include "Falcon.h"
#include "Bomber.h"
#include "ShipmanFactory.h"
#include "CommanderFactory.h"
#include "AdmiralFactory.h"
#include "Utilities.h"

using namespace std;
class Model {
private:
    static shared_ptr<Model> instance;

    vector<shared_ptr<FortressStar>> fortress;
    vector<shared_ptr<SpaceStation>> spaceStations;
    vector<shared_ptr<Shuttle>> shuttles;
    vector<shared_ptr<Bomber>> bombers;
    vector<shared_ptr<Destroyer>> destroyers;
    vector<shared_ptr<Falcon>> falcons;
    vector<shared_ptr<Rocket>> rockets;
    vector<shared_ptr<ImperialAgent>> shipmans;
    vector<shared_ptr<ImperialAgent>> commanders;
    vector<shared_ptr<ImperialAgent>> admirals;
    CommanderFactory commanderFactory ;
    AdmiralFactory admiralFactory ;
    ShipmanFactory shipmanFactory ;

    Model();

    void createFalcon(const string& name, const string& siteName);
    void createFalcon(const string& name, float x, float y);
    void createShip(const string& type, const string& name, const string& nameAgent, const string& nameSite);
    void createShip(const string& type, const string& name, const string& nameAgent, float x, float y);
    void createAgent(const string& typeAgent, const string& nameAgent);


    // user commands
    void shoot(const vector<string>& v);
    void course(const vector<string>& v);
    void position(const vector<string>& v);
    void destination(const vector<string>& v);
    void attack(const vector<string>& v);
    void stop(const vector<string>& v);
    void start_supply(const vector<string>& v);
    void status(const vector<string>& v)const;

public:

    static Model& getInstance();
    Model(const Model& m) = delete;
    Model& operator=(const Model& m) = delete;

    enum SpaceShipsType{N,S,B,D,F}; // N says not found

    enum agentExistAndDuty{NOT_ON_DUTY = 0, DUTY = 1, NOT_EXIST = 2};

    //user commands
    void go();
    void man();
    void status()const;

    // when user command ship//
    void command(stringstream& ss);

    // create agent or spaceShit
    void create(stringstream & ss);

    // if existed: return his type by the enum
    SpaceShipsType existSpaceShip(const string& nameShip)const;


   const vector<shared_ptr<FortressStar>>& getFortress()const;
   const vector<shared_ptr<SpaceStation>>& getSpaceStations()const;
   const vector<shared_ptr<Bomber>>& getBombers()const;
   const vector<shared_ptr<Shuttle>>& getShuttles()const;
   const vector<shared_ptr<Falcon>>& getFalcons()const;
   const vector<shared_ptr<Destroyer>>& getDestroyers()const;

    // read from file
    void initConfig(int argc, char *argv[]);

    // find the site with this name and return his location
    Vector locateSite(const string& name)const;

    // find the site with this name and return his Object
    Object locateSiteObject(const string & name)const;

    // check if agent exist and if he is checked although if he is inDuty
    agentExistAndDuty ExistAgent(const string& name)const;

    // set this agent to be in duty
    shared_ptr<ImperialAgent> getInDuty(const string& name)const;

    shared_ptr<ImperialAgent> getAgent(const string& name)const;
};


#endif //EX3_MODEL_H
