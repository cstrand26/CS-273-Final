#include "denizen.h"

#ifndef ALARMED_H
#define ALARMED_H

class Alarmed : public Denizen {
private:
    enum State _currentState; // current state (Ignorant, Alarmed, Zombie)    
public:
    // Constructor
    Alarmed(int id, int districtId) : Denizen(id, districtId) { _currentState = State::Alarmed; }
    State getState() { return _currentState; } // return state
};

#endif