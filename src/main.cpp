#include "Core/simulation_manager.hpp"

using namespace lattice_boltzmann_method;

int main(int argc, char *argv[]) {
    SimulationManager simulation_manager = SimulationManager(argc, argv);
    simulation_manager.Start();
    return 0;
}