#ifndef STEP_SIMULATION_STRATEGY_CPP
#define STEP_SIMULATION_STRATEGY_CPP

#include "step_simulation_strategy.hpp"

namespace lattice_boltzmann_method 
{
    template <int dim>
    void SerialStepSimulationStrategy<dim>::Setup() {
        
    }

    template <int dim>
    void SerialStepSimulationStrategy<dim>::SimulateNextStep() {
        /*
        for ( Node &node : domain_ ) {
            node.Collide();
            node.Propagate();
            callbacks ...
        }
        */
    }
    template<int dim>
    void SerialStepSimulationStrategy<dim>::SimulateUntil(double time) {
        
    }
}
#endif