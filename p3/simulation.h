#ifndef __SIMULATION_H
#define __SIMULATION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "world_type.h"
using namespace std;

/**
 * @brief simulation_t stores all the information needed in the simulation, including user's input arguments.
 * 
 */
struct simulation_t{
    ifstream speciesFile, worldFile;
    int rounds;
    bool ifVervose;
    world_t world;
    int turn;
};

// For functions' comments, see in simulation.cpp file.

int handleArguments(simulation_t* simulation, const int argc, char* const argv[]);

int handleFileInputs(simulation_t* simulation);

void runSimulation(simulation_t* simulation);

#endif