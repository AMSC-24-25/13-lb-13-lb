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

    template <int dim>
    void 
    SimulationManager<dim>::Parse_(std::shared_ptr<StepSimulationStrategyParser<dim>> simulation_strategy_parser,
                       std::shared_ptr<HistoryParser> history_parser,
                       int &argc, char *argv[]) {
        step_strategy_ = simulation_strategy_parser->Parse(argc, argv);
        history_       = history_parser->Parse(argc, argv);
    }
                
    template <int dim>
    void 
    SimulationManager<dim>::ParseFromFile_(std::shared_ptr<StepSimulationStrategyParser<dim>> simulation_strategy_parser,
                               std::shared_ptr<HistoryParser> history_parser,
                               const std::string &path) {
        step_strategy_ = simulation_strategy_parser->ParseFromFile(path);
        history_       = history_parser->ParseFromFile(path);
    }

}
#endif