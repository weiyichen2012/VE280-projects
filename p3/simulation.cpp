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

/**
 * @brief Given op and address, generate corresponding instruction_t.
 * 
 * @param op Given op.
 * @param address Given address.
 * @return instruction_t The instruction_t that includes op and address.
 */
instruction_t generateInstruction(const opcode_t op, const int address = 0){
    instruction_t instruction;
    instruction.op = op;
    instruction.address = address;
    return instruction;
}

/**
 * @brief Input a full instuction that's split into two parts. First only contains the instruction, second leftLine contains the full instruction get rid of the instruction.
 * For example a full instruction: "ifenemy 4    If there is an enemy, go to step 4.". Then instruction = "ifenemy", instruction = "4    If there is an enemy, go to step 4."
 * Handle this instruction and store it in corresponding data structure.
 * 
 * @param simulation Place to store information.
 * @param instruction See in brief part.
 * @param leftLine See in brief part.
 * @return int 0: Success, 1: Error.
 */
int handleOneSpeciesInstruction(simulation_t* simulation, const string instruction, const string leftLine){
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
        int address = atoi(leftLine.c_str());
        if (instruction == "ifempty")
            theSpecies.program[theSpecies.programSize++] = generateInstruction(IFEMPTY, address);
        else if (instruction == "ifwall")
            theSpecies.program[theSpecies.programSize++] = generateInstruction(IFWALL, address);
        else if (instruction == "ifsame")
            theSpecies.program[theSpecies.programSize++] = generateInstruction(IFSAME, address);
        else if (instruction == "ifenemy")
            theSpecies.program[theSpecies.programSize++] = generateInstruction(IFENEMY, address);
        else if (instruction == "go")
            theSpecies.program[theSpecies.programSize++] = generateInstruction(GO, address);
        else{
            cout << "Error: Instruction " << instruction << " is not recognized!" << endl;
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Handles the input of one species.
 * 
 * @param simulation Place to store information.
 * @param speciesFile The file needs to be read.
 * @return int 1: Success, 0: Error.
 */
int handleOneSpeciesFile(simulation_t* simulation, ifstream* speciesFile){
    string line, splitMsg;
    int pos;
    while(getline((*speciesFile), line)){
        if (line == "")
            return 0;

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

/**
 * @brief Handles the input of species file and corresponding individual species file.
 * 
 * @param simulation Place to store information.
 * @return int 1: Success, 0: Error.
 */
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

/**
 * @brief Change the species in creature_t by finding species in world_t, if can't report error.
 * 
 * @param simulation Store the global information.
 * @param species The given species.
 * @param creature The creature that needs to modify its species.
 * @return int 0: Success, 1: Error.
 */
int findSpecies(simulation_t* simulation, const string species, creature_t* creature){
    for (int i = 0; i < (int)simulation->world.numSpecies; ++i)
        if (simulation->world.species[i].name == species){
            creature->species = simulation->world.species + i;
            return 0;
        }
    
    cout << "Error: Species " << species << " not found!" << endl;
    return 1;
}

/**
 * @brief Generate point_t with given r and c.
 * 
 * @param r Given row.
 * @param c Given column
 * @return point_t The point_t that contains r and c.
 */
point_t generatePoint(const int r, const int c){
    point_t point;
    point.r = r;
    point.c = c;
    return point;
}

/**
 * @brief Return a string that has the information of the creature.
 * 
 * @param creature The given creature.
 * @param ifLowerCase True: creature will be lowercased.
 * @return string The expected output.
 */
string printCreature(const creature_t* creature, bool ifLowerCase = false){
    string returnString;
    if (ifLowerCase)
        returnString += "creature (";
    else
        returnString += "Creature (";
    returnString += creature->species->name + " " + directName[creature->direction] + " " + to_string(creature->location.r) + " " + to_string(creature->location.c) + ")";
    return returnString;
}

/**
 * @brief Modifies a creature in world.creature.
 * 
 * @param simulation Place to store information.
 * @param species The species of creature.
 * @param direction The direction of creature.
 * @param row The row of creature.
 * @param column The column of creature.
 * @return int 0: Success, 1: Error.
 */
int handleOneCreature(simulation_t* simulation, const string species, const string direction, const int row, const int column){
    unsigned int& numCreatures = simulation->world.numCreatures;
    creature_t& creature = simulation->world.creatures[numCreatures];
    creature.programID = 0;

    if (findSpecies(simulation, species, &creature))
        return 1;
    
    if (direction == "east")
        creature.direction = EAST;
    else if (direction == "south")
        creature.direction = SOUTH;
    else if (direction == "west")
        creature.direction = WEST;
    else if (direction == "north")
        creature.direction = NORTH;
    else{
        cout << "Error: Direction " << direction << " is not recognized!" << endl;
        return 1;
    }

    creature.location = generatePoint(row, column);

    if (row < 0 || row >= (int)simulation->world.grid.height || column < 0 || column >= (int)simulation->world.grid.width){
        cout << "Error: " << printCreature(&creature) << " is out of bound!" << endl << "The grid size is " << simulation->world.grid.height << "-by-" << simulation->world.grid.width << "." << endl;
        return 1;
    }

    if (simulation->world.grid.squares[row][column] != nullptr){
        cout << "Error: " << printCreature(&creature) <<" overlaps with " << printCreature(simulation->world.grid.squares[row][column], true) << "!" << endl;
        return 1;
    }
    else{
        simulation->world.grid.squares[row][column] = &creature;
    }

    return 0;
}

/**
 * @brief Read the world file.
 * 
 * @param simulation Store the information.
 * @return int 0: Success, 1: Error.
 */
int handleWorldFile(simulation_t* simulation){
    ifstream& worldFile = simulation->worldFile;
    world_t& world = simulation->world;

    worldFile >> world.grid.height;
    if (world.grid.height < 1 || world.grid.height > MAXHEIGHT){
        cout << "Error: The grid height is illegal!" << endl;
        return 1;
    }

    worldFile >> world.grid.width;
    if (world.grid.width < 1 || world.grid.width > MAXWIDTH){
        cout << "Error: The grid width is illegal!" << endl;
        return 1;
    }

    simulation->world.numCreatures = 0;
    for (int i = 0; i < (int)world.grid.height; ++i)
        for (int j = 0; j < (int)world.grid.width; ++j)
            simulation->world.grid.squares[i][j] = nullptr;

    string line;
    getline(worldFile, line);
    while (getline(worldFile, line)){
        if (simulation->world.numCreatures == MAXCREATURES){
            cout << "Error: Too many creatures!" << endl << "Maximal number of creatures is " << MAXCREATURES << "." << endl;
            return 1;
        }

        string species, direction;
        int row, column, pos;

        pos = line.find(" ");
        species = line.substr(0, pos);
        line = line.substr(pos + 1, line.size());

        pos = line.find(" ");
        direction = line.substr(0, pos);
        line = line.substr(pos + 1, line.size());

        pos = line.find(" ");
        row = atoi(line.substr(0, pos).c_str());
        line = line.substr(pos + 1, line.size());

        column = atoi(line.c_str());

        if (handleOneCreature(simulation, species, direction, row, column))
            return 1;
        
        simulation->world.numCreatures++;
    }

    return 0;
}

/**
 * @brief Process all the inputs through files.
 * 
 * @param simulation Place to store information.
 * @return int 0: Success, 1: Error.
 */
int handleFileInputs(simulation_t* simulation){
    if (handleSpeciesFile(simulation))
        return 1;

    if (handleWorldFile(simulation))
        return 1;

    return 0;
}

/**
 * @brief Print current state, used for output.
 * 
 * @param grid The grid contains all the information needed.
 */
void printState(grid_t* grid){
    for (int i = 0; i < (int)grid->height; ++i)
        for (int j = 0; j < (int)grid->width; ++j){
            if (grid->squares[i][j] == nullptr)
                cout << "____";
            else
                cout << grid->squares[i][j]->species->name.substr(0, 2) << "_" << directShortName[grid->squares[i][j]->direction];
            
            cout << " ";
            if (j == (int)grid->width - 1)
                cout << endl;
        }
}

/**
 * @brief Print move due to output request.
 * 
 * @param simulation Stores information needed.
 * @param creature The specific creature to be printed.
 * @param instruction What instruction needs to be printed.
 */
void printMove(simulation_t* simulation, creature_t* creature, string instruction){
    if (simulation->ifVervose)
        cout << "Instruction " << creature->programID + 1 << ": " << instruction << endl;
    else
        if (instruction == "hop" || instruction == "left" || instruction == "right" || instruction == "infect")
            cout << instruction << endl;
}

/**
 * @brief Output the position the creature is facing.
 * 
 * @param creature The specific creature
 * @return point_t The position
 */
point_t newCreaturePos(creature_t* creature){
    int dx[4] = {0, 1,  0, -1}, dy[4] = {1, 0, -1,  0};
    int oldX = creature->location.r, oldY = creature->location.c;
    point_t newPos;
    newPos.r = oldX + dx[creature->direction];
    newPos.c = oldY + dy[creature->direction];
    return newPos;
}

/**
 * @brief Make the creature's program go on 1 step.
 * 
 * @param creature The specific creature.
 */
void moveCreatureProgram(creature_t* creature){
    creature->programID = (creature->programID + 1) % (creature->species->programSize);
}

/**
 * @brief Handle Hop action of creature.
 * 
 * @param simulation 
 * @param creature 
 */
void creatureHop(simulation_t* simulation, creature_t* creature){
    printMove(simulation, creature, "hop");
    moveCreatureProgram(creature);
    int oldX = creature->location.r, oldY = creature->location.c;
    point_t newPos = newCreaturePos(creature);
    int x = newPos.r, y = newPos.c;
    world_t& world = simulation->world;
    if (x < 0 || y < 0 || x >= (int)world.grid.height || y >= (int)world.grid.width || world.grid.squares[x][y] != nullptr)
        return;
    world.grid.squares[x][y] = world.grid.squares[oldX][oldY];
    world.grid.squares[oldX][oldY] = nullptr;
    creature->location.r = x;
    creature->location.c = y;
    
}

/**
 * @brief Handle Left action of creature.
 * 
 * @param simulation 
 * @param creature 
 */
void creatureLeft(simulation_t* simulation, creature_t* creature){
    printMove(simulation, creature, "left");
    moveCreatureProgram(creature);
    if (creature->direction == EAST)
        creature->direction = NORTH;
    else
        creature->direction = (direction_t)(creature->direction - 1);
}

/**
 * @brief Handle Right action of creature.
 * 
 * @param simulation 
 * @param creature 
 */
void creatureRight(simulation_t* simulation, creature_t* creature){
    printMove(simulation, creature, "right");
    moveCreatureProgram(creature);
    creature->direction = (direction_t)((creature->direction + 1) % 4);
}

/**
 * @brief Handle Infect action of creature.
 * 
 * @param simulation 
 * @param creature 
 */
void creatureInfect(simulation_t* simulation, creature_t* creature){
    printMove(simulation, creature, "infect");
    moveCreatureProgram(creature);
    point_t newPos = newCreaturePos(creature);
    int x = newPos.r, y = newPos.c;
    world_t& world = simulation->world;
    if (x < 0 || y < 0 || x >= (int)world.grid.height || y >= (int)world.grid.width || world.grid.squares[x][y] == nullptr)
        return;
    world.grid.squares[x][y]->species = creature->species;
    world.grid.squares[x][y]->programID = 0;
}

/**
 * @brief Handle IfEmpty action of creature.
 * 
 * @param simulation 
 * @param creature 
 */
void creatureIfEmpty(simulation_t* simulation, creature_t* creature){
    printMove(simulation, creature, "ifempty " + to_string(creature->species->program[creature->programID].address));
    int address = creature->species->program[creature->programID].address - 1;
    moveCreatureProgram(creature);
    point_t newPos = newCreaturePos(creature);
    int x = newPos.r, y = newPos.c;
    world_t& world = simulation->world;
    if (x < 0 || y < 0 || x >= (int)world.grid.height || y >= (int)world.grid.width || world.grid.squares[x][y] != nullptr)
        return;
    creature->programID = address;
}

/**
 * @brief Handle IfWall action of creature.
 * 
 * @param simulation 
 * @param creature 
 */
void creatureIfWall(simulation_t* simulation, creature_t* creature){
    printMove(simulation, creature, "ifwall " + to_string(creature->species->program[creature->programID].address));
    int address = creature->species->program[creature->programID].address - 1;
    moveCreatureProgram(creature);
    point_t newPos = newCreaturePos(creature);
    int x = newPos.r, y = newPos.c;
    world_t& world = simulation->world;
    if (x < 0 || y < 0 || x >= (int)world.grid.height || y >= (int)world.grid.width)
        creature->programID = address;
}

/**
 * @brief Handle IfSame action of creature.
 * 
 * @param simulation 
 * @param creature 
 */
void creatureIfSame(simulation_t* simulation, creature_t* creature){
    printMove(simulation, creature, "ifsame " + to_string(creature->species->program[creature->programID].address));
    int address = creature->species->program[creature->programID].address - 1;
    moveCreatureProgram(creature);
    point_t newPos = newCreaturePos(creature);
    int x = newPos.r, y = newPos.c;
    world_t& world = simulation->world;
    if (x < 0 || y < 0 || x >= (int)world.grid.height || y >= (int)world.grid.width || world.grid.squares[x][y] == nullptr)
        return;
    if (world.grid.squares[x][y]->species == creature->species)
        creature->programID = address;
}

/**
 * @brief Handle IfEnemy action of creature.
 * 
 * @param simulation 
 * @param creature 
 */
void creatureIfEnemy(simulation_t* simulation, creature_t* creature){
    printMove(simulation, creature, "ifenemy " + to_string(creature->species->program[creature->programID].address));
    int address = creature->species->program[creature->programID].address - 1;
    moveCreatureProgram(creature);
    point_t newPos = newCreaturePos(creature);
    int x = newPos.r, y = newPos.c;
    world_t& world = simulation->world;
    if (x < 0 || y < 0 || x >= (int)world.grid.height || y >= (int)world.grid.width || world.grid.squares[x][y] == nullptr)
        return;
    if (world.grid.squares[x][y]->species != creature->species)
        creature->programID = address;
}

/**
 * @brief Handle Go action of creature.
 * 
 * @param simulation 
 * @param creature 
 */
void creatureGo(simulation_t* simulation, creature_t* creature){
    printMove(simulation, creature, "go " + to_string(creature->species->program[creature->programID].address));
    creature->programID = creature->species->program[creature->programID].address - 1;
}

/**
 * @brief Handle the top action of the creature
 * 
 * @param simulation 
 * @param creature 
 */
void creatureAction(simulation_t* simulation, creature_t* creature){
    bool ifUnfinished = true;
    instruction_t* program = creature->species->program;
    while (ifUnfinished){
        switch (program[creature->programID].op){
            case HOP:
                ifUnfinished = false;
                creatureHop(simulation, creature);
                break;
            
            case LEFT:
                ifUnfinished = false;
                creatureLeft(simulation, creature);
                break;

            case RIGHT:
                ifUnfinished = false;
                creatureRight(simulation, creature);
                break;

            case INFECT:
                ifUnfinished = false;
                creatureInfect(simulation, creature);
                break;

            case IFEMPTY:
                creatureIfEmpty(simulation, creature);
                break;

            case IFWALL:
                creatureIfWall(simulation, creature);
                break;

            case IFSAME:
                creatureIfSame(simulation, creature);
                break;
            
            case IFENEMY:
                creatureIfEnemy(simulation, creature);
                break;

            case GO:
                creatureGo(simulation, creature);
                break;

            default:
                ifUnfinished = false;
                cout << "Error in creatureAction, default" << endl;
                creature->programID++;
                break;
        }
    }
}

/**
 * @brief Run the simulation by specific indexes.
 * 
 * @param simulation 
 */
void runSimulation(simulation_t* simulation){
    simulation->turn = 0;
    cout << "Initial state" << endl;
    printState(&simulation->world.grid);
    for (int i = 0; i < simulation->rounds; ++i){
        cout << "Round " << (i + 1) << endl;
        for (int j = 0; j < (int)simulation->world.numCreatures; ++j){
            cout << printCreature(simulation->world.creatures + j) << " takes action:";
            if (simulation->ifVervose)
                cout << endl;
            else
                cout << " ";
            creatureAction(simulation, simulation->world.creatures + j);
            if (simulation->ifVervose)
                printState(&simulation->world.grid);
        }
        if (!simulation->ifVervose)
            printState(&simulation->world.grid);
    }
}