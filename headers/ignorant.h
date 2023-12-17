#include "denizen.h"

#ifndef IGNORANT_H
#define IGNORANT_H

class Ignorant : public Denizen {
private:
    enum State _currentState; // current state (Ignorant, Alarmed, Zombie)
public:
    // constructor
    Ignorant(int id, int districtId) : Denizen(id, districtId) { _currentState = State::Ignorant; }
    State getState() { return _currentState; } // return state
};

#endif