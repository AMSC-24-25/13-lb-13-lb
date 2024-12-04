#include "simulation_manager.hpp"

namespace lattice_boltzmann_method 
{

    void SimulationManager::Start() {
        this->LoadDomain();
        this->SetupDomain();

        if( step_strategy_ ) 
            step_strategy_->SimulateNextStep();
    }

    void SimulationManager::LoadDomain() {

    }

    void SimulationManager::SetupDomain() {

    }

}