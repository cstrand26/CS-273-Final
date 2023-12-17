#include <time.h>
#include <stdlib.h>
#include "simulation.h"
#include <iostream>
#include "utility.h"
using namespace utility;


int main() {
  srand(time(NULL));
  Simulation zombieSimulation(NUM_DAYS);
  zombieSimulation.initialize();
  try {
    zombieSimulation.run();
  }
  catch (const std::exception &e)
  {
    std::cerr << "An error occurred: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}