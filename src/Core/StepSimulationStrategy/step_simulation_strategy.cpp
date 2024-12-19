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

    template<int dim>
    void SerialStepSimulationStrategy<dim>::Initialize(std::shared_ptr<Domain<dim>> domain, 
                                        std::vector<std::shared_ptr<NodeCallback<dim>>> node_callbacks,
                                        double starting_time,
                                        double time_step) {
        this->Initialize_(domain, node_callbacks, starting_time, time_step);
    }

    template <int dim>
    void SerialStepSimulationStrategy<dim>::Setup() {
        const std::vector<int> subdomain_labels = {0};
        this->domain_->Partition(subdomain_labels);
        subdomain_ = this->domain_->GetSubDomainPtr(0);
    }

    template <int dim>
    void SerialStepSimulationStrategy<dim>::SimulateNextStep() {
        for ( std::shared_ptr<Node<dim>> &nodePtr : *subdomain_ ) {
            nodePtr->Collide();
        }
        for ( std::shared_ptr<Node<dim>> &nodePtr : *subdomain_ ) {
            nodePtr->Propagate();
            this->RunConstCallbacks(*nodePtr);
        }

        this->current_time_ += this->time_step_;
    }
}

#endif // STEP_SIMULATION_STRATEGY_CPP
