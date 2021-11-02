#include "simulation.h"
using namespace std;

/**
 * @brief Print Cannot open file Error with given filename.
 * 
 * @param filename The file that cannot be open.
 */
void printCannotOpenFile(const char* filename){
    cout << "Error: Cannot open file " << filename << "!" << endl;
}

/**
 * @brief Process arguments. If there's error return 1 and print error msg, else return 0.
 * 
 * @param simulation Store information in simulation.
 * @param argc User given argc in main function.
 * @param argv User given argv in main function.
 * @return int 0: Success, 1: Error.
 */
int handleArguments(simulation_t* simulation, const int argc, char* const argv[]){
    if (argc < 4){
        cout << "Error: Missing arguments!" << endl << "Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]" << endl;
        return 1;
    }

    simulation->speciesFile.open(argv[1]);
    if (!simulation->speciesFile){
        printCannotOpenFile(argv[1]);
        return 1;
    }

    simulation->worldFile.open(argv[2]);
    if (!simulation->worldFile){
        printCannotOpenFile(argv[2]);
        return 1;
    }

    simulation->rounds = atoi(argv[3]);
    if (simulation->rounds < 0){
        cout << "Error: Number of simulation rounds is negative!" << endl;
        return 1;
    }
    if (argc >= 5 && ((string)argv[4] == "v" || (string)argv[4] == "verbose"))
        simulation->ifVervose = true;
    else
        simulation->ifVervose = false;


    return 0;
}

instruction_t generateInstruction(opcode_t op, int address = 0){
    instruction_t instruction;
    instruction.op = op;
    instruction.address = address;
}

int handleOneSpeciesInstruction(simulation_t* simulation, string instruction, string leftLine){
    // cout << "In handleOneSpeciesInstruction " << instruction << "|" << leftLine << endl;
    unsigned int& numSpecies = simulation->world.numSpecies;
    species_t& theSpecies = simulation->world.species[numSpecies];

    if (theSpecies.programSize == MAXPROGRAM){
        cout << "Error: Too many instructions for species " << theSpecies.name << "!" << endl << "Maximal number of instructions is " << MAXPROGRAM << "." << endl;
        return 1;
    }

    if (instruction == "hop")
        theSpecies.program[theSpecies.programSize++] = generateInstruction(HOP);
    else if (instruction == "left")
        theSpecies.program[theSpecies.programSize++] = generateInstruction(LEFT);
    else if (instruction == "right")
        theSpecies.program[theSpecies.programSize++] = generateInstruction(RIGHT);
    else if (instruction == "infect")
        theSpecies.program[theSpecies.programSize++] = generateInstruction(INFECT);
    else{
        cout << "Error: Instruction " << instruction << " is not recognized!" << endl;
        return 1;
    }
    return 0;
}

int handleOneSpeciesFile(simulation_t* simulation, ifstream* speciesFile){
    string line, splitMsg;
    int pos;
    while(getline((*speciesFile), line)){
        if (line == ""){
            // cout << "Empty" << endl;
            return 0;
        }
        // cout << line << endl;

        pos = line.find(" ");
        if (pos == -1){
            if (handleOneSpeciesInstruction(simulation, line, ""))
                return 1;
        }
        else
            if (handleOneSpeciesInstruction(simulation, line.substr(0, pos), line.substr(pos + 1, line.size())))
                return 1;
    }

    return 0;    
}

int handleSpeciesFile(simulation_t* simulation){
    ifstream& speciesFile = simulation->speciesFile;
    string directory;
    speciesFile >> directory;

    string speciesName;
    while (speciesFile >> speciesName){
        ifstream tmpSpecies;
        tmpSpecies.open(directory + "/" + speciesName);
        if (!tmpSpecies){
            printCannotOpenFile((directory + "/" + speciesName).c_str());
            return 1;
        }

        if (simulation->world.numSpecies == MAXSPECIES){
            cout << "Error: Too many species!" << endl << "Maximal number of species is " << MAXSPECIES << "." << endl;
            return 1;
        }

        simulation->world.species[simulation->world.numSpecies].name = speciesName;
        simulation->world.species[simulation->world.numSpecies].programSize = 0;

        if (handleOneSpeciesFile(simulation, &tmpSpecies))
            return 1;
        
        simulation->world.numSpecies++;
    }

    return 0;
}

int handleFileInputs(simulation_t* simulation){
    if (handleSpeciesFile(simulation))
        return 1;

    return 0;
}