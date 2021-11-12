#include "simulation1.h"
#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {
    try {
        if (argc < 4) throw ARG_MISSING;
        int round = stoi(string(argv[3]));
        if (round < 0) throw ROUND_NEG;

        World world;
        world.init(string(argv[1]), string(argv[2]));

        bool verbose = (argc > 4) && (std::string(argv[4]) == "v" || std::string(argv[4]) == "verbose");

        for (int i = 1; i <= round; i++) {
            std::cout << "Round " << i << '\n';
            world.run(verbose);
        }
    } catch (my_error_t e){
        switch (e) {
        case ARG_MISSING:
            cout << "Error: Missing arguments!\nUsage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]\n";
            break;
        case ROUND_NEG:
            cout << "Error: Number of simulation rounds is negative!\n";
            break;
        case SPECIES_MAX:
            cout << "Error: Too many species!\nMaximal number of species is " << MAXSPECIES << ".\n";
            break;
        case CREATURE_MAX:
            cout << "Error: Too many creatures!\nMaximal number of creatures is " << MAXCREATURES << ".\n";
            break;
        case HEIGHT_MAX:
            cout << "Error: The grid height is illegal!\n";
            break;
        case WIDTH_MAX:
            cout << "Error: The grid width is illegal!\n";
            break;
        case FILE_ERR:
        case INSTR_MAX:
        case INSTR_UNKNOWN:
        case SPECIES_UNKNOWN:
        case DIR_UNKNOWN:
        case BOUND_OUT:
        case CREATURE_OVERLAP:
            // These 7 errors need printing with additional information.
            // Printing done just before throw.
            ;
        }
    }

    return 0;
}
