#ifndef SIMULATION_MANAGER_CPP
#define SIMULATION_MANAGER_CPP
#include "simulation_manager.hpp"

namespace lattice_boltzmann_method 
{

    template<int dim>
    void SimulationManager<dim>::Start() {
        this->LoadDomain();
        this->SetupDomain();

        if( step_strategy_ ) 
            step_strategy_->SimulateNextStep();
    }
    
    template<int dim>
    void SimulationManager<dim>::LoadDomain() {

    }

    template<int dim>
    void SimulationManager<dim>::SetupDomain() {

    }

}
#endif