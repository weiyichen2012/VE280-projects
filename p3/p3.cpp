#include "simulation.h"
using namespace std;

int main(int argc, char* argv[]){
    simulation_t simulation;
    simulation.world.numCreatures = simulation.world.numSpecies = 0;

    if (handleArguments(&simulation, argc, argv))
        return 0;
    
    if (handleFileInputs(&simulation))
        return 0;

    runSimulation(&simulation);
    return 0;
}