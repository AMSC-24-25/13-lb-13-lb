#include "step_simulation_strategy.hpp"

namespace lattice_boltzmann_method 
{
    void SerialStepSimulationStrategy::SimulateNextStep() {
        /*
        for ( Node &node : domain_ ) {
            node.Collide();
            node.Propagate();
            callbacks ...
        }
        */
    }
    void SerialStepSimulationStrategy::SimulateUntil(double time) {
        
    }
}