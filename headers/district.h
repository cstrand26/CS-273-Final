#ifndef DISTRICT_H
#define DISTRICT_H

#include "denizen.h"
#include "alarmed.h"
#include "ignorant.h"
#include "zombie.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>

class District
{
private:
    int _id; // unique identifier for the district
    std::string _name; // name
    std::vector<Denizen*> _denizens; // container of denizens in the district
    std::unordered_map<Denizen::State, int> _stateCounts; // track the number of denizens in each state
    std::vector<Alarmed*> _alarmed; // container of all alarmed denizens
    std::vector<Ignorant*> _ignorant; // container of all ignorant denizens
    std::vector<Zombie*> _zombie; // container of all zombie denizens
public:
    District(int id, std::string name = "district "){ _id = id; _name = (name + std::to_string(id)); } // constructor
    int getId(){ return _id ;} // return unique id
    std::string getName() { return _name; } // return name
    std::unordered_map<Denizen::State, int> getStateCounts() const { return _stateCounts; } // returns stateCounts
    auto getDenizens(int index) {return _denizens[index]; } // returns denizen from denizens vector
    Alarmed* getAlarmed(int index) { return _alarmed[index]; } // returns whole alarmed denizen from alarmed vector
    Ignorant* getIgnorant(int index) { return _ignorant[index]; } // returns whole ignorant denizen from ignorant vector
    Zombie* getZombie(int index) { return _zombie[index]; } // returns whole zombie denizen from zombie vector
    double getIgnorantPop(){ return _ignorant.size(); } // return the number of alarmed people
    double getAlarmedPop(){ return _alarmed.size(); } // return the number of alarmed people
    double getZombiePop(){ return _zombie.size(); } // returns the number of zombies
    double getAllPop(){ return _denizens.size(); } // returns total population
    double getPeoplePop(){ return ( _alarmed.size() + _ignorant.size() ); } // returns total people
    double getRealityPop(){ return ( _alarmed.size() + _zombie.size() ); } // return the number of alarmed people
    void addDenizen(Alarmed* denizen); // add denizen for alarmed
    void addDenizen(Ignorant* denizen); // add denizen for Ignorant
    void addDenizen(Zombie* denizen); // add denizen for Zombie
    void removeDenizen(int denizenId); // removes denizen based on their unique ID number
    void createZombie(Alarmed* alarmed); // for creating Zombie copy of Alarmed and deleting old Alarmed
    void createZombie(Ignorant* ignorant); // for creating Zombie copy of Ignorant and deleting old Ignorant
    void createAlarmed(Ignorant* ignorant); // for creating Alarmed copy of Ignorant and deleting old Ignorant
    void alarmCheck(); // runs probability to change ignorant to alarmed and runs change
    void biteCheck(); // runs probability to change non-zombie to zombie and runs change
    void moveCheck(std::queue<Ignorant*> &toMoveIg, std::queue<Alarmed*> &toMoveAl, std::queue<Zombie*> &toMoveZom); // add denizens to queue to be moved.
};

#endif
