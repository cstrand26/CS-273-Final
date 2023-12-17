#include "denizen.h"
#include "alarmed.h"
#include "ignorant.h"
#include "zombie.h"
#include "district.h"
#include "utility.h"
#include <vector>
#include <unordered_map>
#include <queue>
#include <typeinfo>
using namespace utility;

void District::addDenizen(Alarmed* alarmed){
    alarmed->setDistrictID(_id);
    _denizens.push_back(alarmed); // adds to population of district
    _alarmed.push_back(alarmed); // adds to alarmed in distraict
    _stateCounts[alarmed->getState()]++;
}
void District::addDenizen(Zombie* zombie){
    zombie->setDistrictID(_id); // sets district id
    _denizens.push_back(zombie); // adds to population of district
    _zombie.push_back(zombie); // adds to zombies in district
    _stateCounts[zombie->getState()]++;
}
void District::addDenizen(Ignorant* ignorant){
    ignorant->setDistrictID(_id); // sets district id
    _denizens.push_back(ignorant); // adds to population of district
    _ignorant.push_back(ignorant); // adds to ignorant in district
    _stateCounts[ignorant->getState()]++;
}
void District::removeDenizen(int denizenId){
    for (auto it = _denizens.begin(); it != _denizens.end();){ // search through all denizens
        if ((*it)->getId() == denizenId){ // until denizen with the proper id is found
            if (typeid(*(*it)) == typeid(Alarmed)){
                for (auto zit = _alarmed.begin(); zit != _alarmed.end();){ // search through all the alarmed
                    if ((*zit)->getId() == denizenId){ // until alarmed with the proper id is found
                        _alarmed.erase(zit);
                        break;
                    } else {
                        ++zit;
                    }
                }
            } else if (typeid(*(*it)) == typeid(Zombie)){
                for (auto zit = _zombie.begin(); zit != _zombie.end();){ // search through all the zombies
                    if ((*zit)->getId() == denizenId){ // until zombie with the proper id is found
                        _zombie.erase(zit);
                        break;
                    } else {
                        ++zit;
                    }
                }
            } else if (typeid(*(*it)) == typeid(Ignorant)){
                for (auto zit = _ignorant.begin(); zit != _ignorant.end();){ // search through all the ignorant
                    if ((*zit)->getId() == denizenId){ // until ignorant with the proper id is found
                        _ignorant.erase(zit);
                        break;
                    } else {
                        ++zit;
                    }
                }
            }
            _stateCounts[(*it)->getState()]--;
            _denizens.erase(it);  // Update iterator after erasing
            break;
        } else {
            ++it;
        }
    }   
}
void District::createZombie(Alarmed* alarmed){
    Zombie* temp = new Zombie(alarmed->getId(), alarmed->getDistrictId()); // create new Zombie
    removeDenizen(alarmed->getId()); // remove the Alarmed from population
    addDenizen(temp); // add the Zombie to population
    delete alarmed; // delete Alarmed
}
void District::createZombie(Ignorant* ignorant){
    Zombie* temp = new Zombie(ignorant->getId(), ignorant->getDistrictId()); // create new Zombie
    removeDenizen(ignorant->getId()); // remove the Ignorant from population
    addDenizen(temp); // add the Zombie to population
    delete ignorant; // delete Ignorant
}
void District::createAlarmed(Ignorant* ignorant){
    Alarmed* temp = new Alarmed(ignorant->getId(), ignorant->getDistrictId()); // create new Alarmed
    removeDenizen(ignorant->getId()); // remove the Ignorant from population
    addDenizen(temp); // add the Alarmed to population
    delete ignorant; // delete Ignorant
}
void District::alarmCheck(){
    double alarmChance = (getRealityPop()*IGNORANT_TO_ALARMED_MAX_PROB)/getAllPop(); // generate chance of becoming alarmed
    std::queue<Ignorant*> transition; // container for holding ignorant to alarmed
    if (!_ignorant.empty()){
        for (auto it = _ignorant.begin(); it != _ignorant.end(); ++it){ // search through all ignorant denizens
            if (checkProbability(alarmChance)){ // if true
                transition.push(*it); // add to list
            }
        }
    }    
    while (!transition.empty()){
        createAlarmed(transition.front()); // change from ignorant to alarmed
        transition.pop(); // remove from list
    }
}
void District::biteCheck(){
    double biteAlarmedChance = (getZombiePop()*ALARMED_TO_ZOMBIE_MAX_PROB)/getAllPop(); // generate chance of alarmed becoming zombie
    double biteIgnorantChance = (getZombiePop()*IGNORANT_TO_ZOMBIE_MAX_PROB)/getAllPop(); // generate chance of ignorant becoming zombie
    std::queue<Ignorant*> transitionIgnorant; // container for holding ignorant to zombie
    std::queue<Alarmed*> transitionAlarmed; // container for holding alarmed to zombie
    for (auto it = _ignorant.begin(); it != _ignorant.end(); ++it){ // search through all ignorant denizens
        if (checkProbability(biteIgnorantChance)){ // if true
            transitionIgnorant.push(*it); // add to list
        }
    }

    for (auto it = _alarmed.begin(); it != _alarmed.end(); ++it){ // search through all ignorant denizens
        if (checkProbability(biteAlarmedChance)){ // if true
            transitionAlarmed.push(*it); // add to list
        }
    }  
    while (!transitionIgnorant.empty()){
        createZombie(transitionIgnorant.front()); // change from ignorant to alarmed
        transitionIgnorant.pop(); // remove from list
    }
    while (!transitionAlarmed.empty()){
        createZombie(transitionAlarmed.front()); // change from ignorant to alarmed
        transitionAlarmed.pop(); // remove from list
    }
}
void District::moveCheck(std::queue<Ignorant*> &toMoveIg, std::queue<Alarmed*> &toMoveAl, std::queue<Zombie*> &toMoveZom){
    for (auto it = _ignorant.begin(); it != _ignorant.end(); ++it){ // search through all ignorant
        if (checkProbability(IGNORANT_MOVE_PROB)){ // if yes
            toMoveIg.push(*it); // add to list
        }
    }
    for (auto it = _alarmed.begin(); it != _alarmed.end(); ++it){ // search through all ignorant
        if (checkProbability(ALARMED_MOVE_PROB)){ // if yes
            toMoveAl.push(*it); // add to list
        }
    }
    for (auto it = _zombie.begin(); it != _zombie.end(); ++it){ // search through all ignorant
        if (checkProbability(ZOMBIE_MOVE_PROB)){ // if yes
            toMoveZom.push(*it); // add to list
        }
    } 
}