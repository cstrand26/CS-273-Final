#include <vector>
#include <iostream>

#ifndef DENIZEN_H
#define DENIZEN_H

class Denizen { // purely virtual class
public:
    enum class State {
    Ignorant,
    Alarmed,
    Zombie
    };
private:
    int _id;            // unique identifier for the denizen
    int _districtId;    // current district ID where the denizen is located
public:
    // constructor
    Denizen(int id, int districtId) {_id = id; _districtId = districtId;}// constructor
    int getId() const { return _id; } // return unique id
    int getDistrictId() const { return _districtId; } // return district (location) id
    void setDistrictID(int id){ _districtId = id; } 
    virtual State getState() =0; // return state
};

#endif 