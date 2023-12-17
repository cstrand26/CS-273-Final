#include "denizen.h"

#ifndef ZOMBIE_H
#define ZOMBIE_H

class Zombie : public Denizen {
private:
    enum State _currentState; // current state (Ignorant, Alarmed, Zombie)
public:
    // constructor
    Zombie(int id, int districtId) : Denizen(id, districtId) { _currentState = State::Zombie; }
    State getState() { return _currentState; } // return state
};

#endif