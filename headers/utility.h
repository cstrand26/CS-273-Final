#ifndef UTILITIES_H
#define UTILITIES_H

#include <random>

namespace utility
{
    // change as needed
    constexpr double IGNORANT_TO_ZOMBIE_MAX_PROB = 0.1;  // The max chance of ignorant turning into zombie
    constexpr double IGNORANT_TO_ALARMED_MAX_PROB = 0.1; // The max chance of ignorant turning into alarmed
    constexpr double ALARMED_TO_ZOMBIE_MAX_PROB = 0.05;   // The max chance of alarmed turning into zombie
    static constexpr double IGNORANT_MOVE_PROB = 0.1; // adjusts chance of ignorants moving
    static constexpr double ALARMED_MOVE_PROB = .2; // adjusts chance of alarmed moving
    static constexpr double ZOMBIE_MOVE_PROB = .15; // adjusts chance of zombies moving
    constexpr int NUM_DISTRICTS = 4; // adjust number of districts
    constexpr int NUM_DENIZENS = 2000; // adjusts population size
    constexpr int NUM_DAYS = 7; // adjusts nmber of days
    constexpr int TERMINAL_SPEED = 10; // adjusts rate of terminal refresh

    double generateRandomDouble(double min, double max);
    bool checkProbability(double probability);
}

#endif