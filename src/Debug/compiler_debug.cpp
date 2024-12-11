#include "compiler_debug.hpp"

namespace lattice_boltzmann_method {

    template class SimulationManager<2>;
    template class SimulationManager<3>;

    template class SerialStepSimulationStrategy<2>;
    template class SerialStepSimulationStrategy<3>;

    template class OpenMPStepSimulationStrategy<2>;
    template class OpenMPStepSimulationStrategy<3>;
}