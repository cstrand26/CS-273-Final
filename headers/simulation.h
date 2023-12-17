#ifndef SIMULATION_H
#define SIMULATION_H

#include "district.h"
#include "denizen.h"
#include <list>
#include <set>
#include <unordered_map>
#include <vector>
#include <queue>

    class Simulation
    {
    private:
        int _numDays;                     // total number of days for the simulation
        std::vector<District> _districts; // vector containing all districts in the simulation
        int _currentDay;                  // current day in the simulation
        int _currentTimeStep;             // current time step (hour) within the current day
        int _nextDenizenId;               // Unique identifier for each denizen
        int _nextDistrictId;
        std::queue<Ignorant*> _toMoveIg;    // queue for moving Ignorant
        std::queue<Alarmed*> _toMoveAl;    // queue for moving Alarmed
        std::queue<Zombie*> _toMoveZom;    // queue for moving Zombie
        std::unordered_map<int, std::vector<int>> _adjacencyList; 

    public:
        // initializes the simulation with the total number of days and the graph
        Simulation(int numDays);
        void addDistrict(); // adds district to simulation
        void moveAllDistrict(); // moves denizens
        void actionEachDistrict(); // changes denizens to alarmed and zombies
        void initialize();
        void run();
        void distributeInitialPopulation();
        void outputToCSV(const std::string &filename);
        void displaySimulationState();
    };

#endif
