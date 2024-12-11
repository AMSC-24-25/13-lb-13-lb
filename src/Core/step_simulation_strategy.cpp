#ifndef STEP_SIMULATION_STRATEGY_CPP
#define STEP_SIMULATION_STRATEGY_CPP

#include "step_simulation_strategy.hpp"

namespace lattice_boltzmann_method 
{
    template<int dim>
    void StepSimulationStrategy<dim>::SimulateUntil(double time) {
        while ( current_time_ < time ) {
            this->SimulateNextStep();
        }
    }

    template <int dim>
    void SerialStepSimulationStrategy<dim>::Setup() {
        this->domain_.Partition({0});
        subdomain_ = this->domain_.GetSubDomainPtr(0);
    }

    template <int dim>
    void SerialStepSimulationStrategy<dim>::SimulateNextStep() {
        for ( Node<dim> &node : subdomain_ ) {
            node.Collide();
            node.Propagate();
            this->RunConstCallbacks(node);
        }
        this->current_time_ += this->time_step_;
    }
}
#endif