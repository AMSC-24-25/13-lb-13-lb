#include "Core/simulation_manager.hpp"

using namespace lattice_boltzmann_method;

int main(int argc, char *argv[]) {
    SimulationManager<2> simulation_manager = SimulationManager<2>(argc, argv);
    simulation_manager.Start();
    return 0;
}