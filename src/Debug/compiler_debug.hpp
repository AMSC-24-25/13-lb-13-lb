#ifndef COMPILER_DEBUG_HPP
#define COMPILER_DEBUG_HPP

#include "../Core/simulation_manager.hpp"
#include "../Core/step_simulation_strategy.hpp"

namespace lattice_boltzmann_method {

    template class SimulationManager<2>;
    template class SimulationManager<3>;

    template class SerialStepSimulationStrategy<2>;
    template class SerialStepSimulationStrategy<3>;

}

#endif // COMPILER_DEBUG_HPP
