#ifndef STEP_SIMULATION_STRATEGY_PARSER_CPP
#define STEP_SIMULATION_STRATEGY_PARSER_CPP

#include "step_simulation_strategy_parser.hpp"

namespace lattice_boltzmann_method 
{
    template <int dim>
    std::ostream& 
    StepSimulationStrategyParser<dim>::PrintTerminalHelp(std::ostream &output_stream) {
        // TODO
        return output_stream;
    }

    template <int dim>
    std::ostream&
    StepSimulationStrategyParser<dim>::PrintFileHelp(std::ostream &output_stream) {
        // TODO
        return output_stream;
    }

    template<int dim>
    std::shared_ptr<StepSimulationStrategy<dim>> 
    StepSimulationStrategyParser<dim>::Parse(int &argc, char *argv[]) {
        std::shared_ptr<StepSimulationStrategy<dim>> strategy;
        for ( int i=0; i<argc; i++ ) {
            if (std::strcmp(argv[i], "SerialStepSimulationStrategy")) {
                strategy = std::make_unique<SerialStepSimulationStrategy<dim>>();
                // TODO: remove read value and shift others
                //argc--;
                return strategy;
            } else if (std::strcmp(argv[i], "OpenMPStepSimulationStrategy")) {
                strategy = std::make_unique<OpenMPStepSimulationStrategy<dim>>();
                // TODO: remove read value and shift others
                //argc--;
                return strategy;
            }
        }
        return nullptr;
    };

    template<int dim>
    std::shared_ptr<StepSimulationStrategy<dim>> 
    StepSimulationStrategyParser<dim>::ParseFromFile(const std::string &path) {
        return nullptr;
    }
}
#endif