#include "simulation.h"
#include <vector>
#include <unordered_map>
#include "district.h"
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include "utility.h"
#include <thread>
#include <iostream>
#include "colors.h"
using namespace utility;

// Constructor
Simulation::Simulation(int numDays) 
    : _numDays(numDays), _currentDay(0), _currentTimeStep(0), _nextDenizenId(0), _nextDistrictId(0) {}
void Simulation::addDistrict(){ // add new districts
    District newDistrict(_nextDistrictId++); // creates new district and iterates through district ID
    std::vector<int> emptyVector; // create a new empty vector
    if (_districts.empty()){ // if this is the first district
        _districts.push_back(newDistrict); // add district to the simulation vector
        _adjacencyList.emplace(newDistrict.getId(), emptyVector); // add a new entry to the adjacency list
    } else { // if not the first distrct
        _districts.push_back(newDistrict); // add district to simulation vector
        // this is so every new district gets connected to an old district and the old district gets connected it the new.
        int districtNeighbor = rand() % (_nextDistrictId-1); // generate a number of another district
        emptyVector.push_back(districtNeighbor); // add it to the vector for the new adjacency list
        _adjacencyList.emplace(newDistrict.getId(), emptyVector); // create new entry 
        _adjacencyList[districtNeighbor].push_back(newDistrict.getId()); // add new district id to adjancency for old district
    }   
}
void Simulation::actionEachDistrict(){ // runs alarm and bites for each district
    for (auto it = _districts.begin(); it != _districts.end(); ++it){
        it->alarmCheck();
        it->biteCheck();
    }
}
////
void Simulation::moveAllDistrict(){ // runs movechecks for every district and then moves them
    for (auto it = _districts.begin(); it != _districts.end(); ++it){ // for every district
        it->moveCheck(_toMoveIg, _toMoveAl, _toMoveZom); // add denizen's to be moved to the queue
    }
    while (!_toMoveIg.empty()){ // until queue is empty
        int random = rand() % _adjacencyList[_toMoveIg.front()->getDistrictId()].size(); // select random district number for adjacent districts
        int newDistrictId = _adjacencyList[_toMoveIg.front()->getDistrictId()][random];
        for (auto it = _districts.begin(); it != _districts.end(); ++it){ // go through all the districts

            if (it->getId() == _toMoveIg.front()->getDistrictId()){ // if old district
                it->removeDenizen(_toMoveIg.front()->getId()); // remove
            }
        }
        for (auto it = _districts.begin(); it != _districts.end(); ++it){
            if (it->getId() == newDistrictId){ // if new district
                it->addDenizen(_toMoveIg.front()); // add
            }
        }
        _toMoveIg.pop();    
    }
    while (!_toMoveAl.empty()){  // until queue is empty
        int leastZombies = -1; // district id with least zombies
        int zombieNum = -1; // number of zombies
        for(auto zit = _adjacencyList[_toMoveAl.front()->getDistrictId()].begin(); zit != _adjacencyList[_toMoveAl.front()->getDistrictId()].end(); ++zit){ // for every district id in adjacency vector for original district
            for (auto it = _districts.begin(); it != _districts.end(); ++it){ // look through all districts
                if (_toMoveAl.front()->getDistrictId() == it->getId() || *zit == it->getId()){ // set leastZombies to district with smallest zombie count
                    if (it->getZombiePop() < zombieNum || zombieNum < 0){
                        leastZombies = it->getId();
                        zombieNum = it->getZombiePop();
                    }
                }    
            }
        }
        if (_toMoveAl.front()->getDistrictId() != leastZombies){
            int complete = 0; // to let us know we're complete    
            for (auto it = _districts.begin(); it != _districts.end(); ++it){ // go through all the districts
                if (it->getId() == _toMoveAl.front()->getDistrictId()){ // if old district
                    it->removeDenizen(_toMoveAl.front()->getId()); // remove
                }
            }    
            for (auto it = _districts.begin(); it != _districts.end(); ++it){
                if (it->getId() == leastZombies){ // if new district
                    it->addDenizen(_toMoveAl.front()); // add
                }                  
            }
        }
        _toMoveAl.pop();     
    }
    while (!_toMoveZom.empty()){  // until queue is empty
        int mostPeople = -1; // district id with most people
        int peopleNum = -1; // number of people
        for(auto zit = _adjacencyList[_toMoveZom.front()->getDistrictId()].begin(); zit != _adjacencyList[_toMoveZom.front()->getDistrictId()].end(); ++zit){ // for every district id in adjacency vector for original district
            for (auto it = _districts.begin(); it != _districts.end(); ++it){ // look through all districts
                if (_toMoveZom.front()->getDistrictId() == it->getId() || *zit == it->getId()){ // set mostPeople to district with largest people count 
                    if (it->getPeoplePop() > peopleNum){
                        mostPeople = it->getId();
                        peopleNum = it->getPeoplePop();
                    }
                }    
            }
        }
        if (_toMoveZom.front()->getDistrictId() != mostPeople){
            int complete = 0; // to let us know we're complete
            for (auto it = _districts.begin(); it != _districts.end(); ++it){ // go through all the districts
                if (it->getId() == _toMoveZom.front()->getDistrictId()){ // if old district
                    it->removeDenizen(_toMoveZom.front()->getId()); // remove
                    complete++;
                }
            }
            for (auto it = _districts.begin(); it != _districts.end(); ++it){ // go through all the districts
                if (it->getId() == mostPeople){ // if new district
                    it->addDenizen(_toMoveZom.front()); // add
                }            
            }
        } 
        _toMoveZom.pop();     
    }
}    
/////
void Simulation::initialize(){
    for (int i = 0; i < utility::NUM_DISTRICTS; ++i){
        addDistrict();
    }
}
void Simulation::run(){
    std::string filename = "simulation_output.csv";
    std::ofstream file(filename);
    file.close();

    distributeInitialPopulation(); // Distribute population first

    // immediate output after initial distribution
    outputToCSV(filename);

    for (_currentDay = 1; _currentDay <= _numDays; ++_currentDay)
    {
        for (_currentTimeStep = 1; _currentTimeStep <= 24; ++_currentTimeStep)
        {
            moveAllDistrict();
            actionEachDistrict();
            outputToCSV(filename);
            displaySimulationState();
        }
    }
}
void Simulation::distributeInitialPopulation(){
    // calculates the population for each district, assuming an even distribution
    int populationPerDistrict = utility::NUM_DENIZENS / _districts.size(); 
    int zombieStart = rand() % _districts.size();
    int alarmedStart = rand() % _districts.size();
    for (auto &district : _districts){
        if (district.getId() == zombieStart){
            Zombie* newZombie = new Zombie (_nextDenizenId++, district.getId());
            district.addDenizen(newZombie);
        }
        if (district.getId() == alarmedStart){
            Alarmed* newAlarmed = new Alarmed (_nextDenizenId++, district.getId());
            district.addDenizen(newAlarmed);
        }
        for (int i = 0; i < populationPerDistrict; ++i){
            Ignorant* newDenizen = new Ignorant (_nextDenizenId++, district.getId());
            district.addDenizen(newDenizen);
        }
    }
}
void Simulation::outputToCSV(const std::string &filename){
    std::ofstream file(filename, std::ios::app);
    // Header for the CSV file
    file << "\nDay " << _currentDay << " Summary:\n";
    file << "Hour, District ID, Ignorant, Alarmed, Zombie, Population\n";
    for (auto &district : _districts) {
        // currentTimeStep
        file << std::setw(2) << _currentTimeStep << ", "
            << std::setw(12) << district.getId() << ", "
            << std::setw(8) << district.getIgnorantPop() << ", "
            << std::setw(7) << district.getAlarmedPop() << ", "
            << std::setw(6) << district.getZombiePop() << ", "
            << std::setw(10) << district.getAllPop() << "\n";
    }
        // Add a line break for readability between time steps
        file << "\n";
}
void clearTerminal()
    {
#ifdef __APPLE__
        std::system("clear");

#else
        std::system("cls");
#endif
    }
std::string stateToString(Denizen::State state)
    {
        switch (state)
        {
        case Denizen::State::Ignorant:
            return "Ignorant";
        case Denizen::State::Alarmed:
            return "Alarmed";
        case Denizen::State::Zombie:
            return "Zombie";
        default:
            return "Unknown?!";
        }
    }
void Simulation::displaySimulationState()
    {
        clearTerminal(); // Clear the terminal for a clean display

        const char *zombieT = R"(
                     ..... .., . ., .   .,....,,.  
                ... . . .. .....  ...,,,,,,.,,,..... . .    
         . . ... . .....   .....,,,,,,,,,,,,,,,,,,.....
             .  ..........,,,,,,,,,,,,,,.,,,,,,,,,,....,, ..               
      ... ..  ....   ,.,,.,.,,.,,.,,,,,,,.,,,.,,,,,,,...., ..... ...      
     .           .  ...,.,,,,,.....,.....,,...,....,,,,,,..  .. ........   
          ..     .,.,...,,.,......,..................,,..,. ... .  ...,.            
      .  .. ................. .,..........................,.....  .,. ... . .   
     .  . ..  . ..............  ....................,..........   ......... .   
     ... . .. ... ......  .... ...................................  . .   ..    
         . . .   ....  ...... ...................... ........  . .....     .    
     . ..  ....  ................... .................... ..   ,  . ....   ..   
      .      ...  ... ........................................      . . ..  .   
      . .        ..  ........  ............ ...................   .     .       
     ..  .  ...    ......     .   ........ .. ....  .     .....  .. . .         
           .   .  . .... . .         . ..,...                .      .    )";
        std::cout << colors.Zombie << zombieT << colors.Clean << std::endl;
        std::cout << colors.Zombie << "  ..  .  ..    .. . .";
        std::cout << colors.Red << "       /0\\" << colors.Clean;
        std::cout << colors.Zombie << "     . .  .,...  .";
        std::cout << colors.Red << "     /0\\" << colors.Clean;
        std::cout << colors.Zombie << "       ..     ." << std::endl;
        std::cout << colors.Zombie << "   .   .     .    . . .";
        std::cout << colors.dim << "     \\0/" << colors.Clean;
        std::cout << colors.Zombie << "      .  ,,   . .";
        std::cout << colors.dim << "      \\0/" << colors.Clean;
        std::cout << colors.Zombie << "      ..";
        const char *zombieB = R"(
     .. .       .. ... ..        ......,     , ...          ...       ..    .   
      .  .     .   ........   ....... .       .......       ...                 
       ..  ..     ..... .......  .  ...   .  . ..       .,.... .                
     .      .    ......, .. ..   .....    ..   ...       . , . ..               
        .  .       ....,         ... ..  ...  ... .         . .        .        
              .        .         .................         .                    
            .                    ..................                             
         .                      .. .. ,. .. ....   .                            
                            ..    ............. .. .  .                         
          .                 .      . . .......  .     .                         
                            ... .                  . .                          
      .                     . .. .                .                             
          .                 ....  ...          ,... . .                         
     .           .           ...... ........   .     .                          
                              ........... . .     ..                            
                                 .... . ..                                      
           .                    . ................                              
                                     ........ .                                 
      .                               . ....                                    
             .                        .  ..                         
                            
  )";
        std::cout << colors.Zombie << zombieB << colors.Clean << std::endl;

        std::cout << "Day " << _currentDay << ", Hour " << _currentTimeStep << ":" << std::endl;
        int totalSurvivors = 0; // Variable to keep track of total survivors

        for (auto &district : _districts)
        {
            auto stateCounts = district.getStateCounts();
            // now a check to see if state counts are empty and if so we will display dead by the name of the state change
            int ignorantCount = stateCounts[Denizen::State::Ignorant];
            int alarmedCount = stateCounts[Denizen::State::Alarmed];
            int zombieCount = stateCounts[Denizen::State::Zombie];

            totalSurvivors += ignorantCount + alarmedCount;
            // Display district states
            std::cout << district.getName() << ": ";
            std::cout << "[Ignorant: " << colors.White << ignorantCount << " " << colors.GreyBG << std::string(ignorantCount / 5, '_') << colors.Clean << "] ";
            std::cout << "[Alarmed: " << colors.gold << alarmedCount << " " << colors.BGorange << std::string(alarmedCount / 5, '_') << colors.Clean << "] ";
            std::cout << "[Zombie: " << colors.Red << zombieCount << " " << colors.BGred << std::string(zombieCount / 5, '_') << colors.Clean << "]" << std::endl;
        }
        std::cout << "\n[Survivors: " << totalSurvivors << " ]" << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(TERMINAL_SPEED)); // delay for visual effect change number as needed
    }