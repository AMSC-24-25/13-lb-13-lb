#ifndef STEP_SIMULATION_STRATEGY_PARSER_HPP
#define STEP_SIMULATION_STRATEGY_PARSER_HPP

#include <string>
#include <cstring>
#include <memory>
#include <iostream>

#include "../step_simulation_strategy.hpp"
#include "../openmp_step_simulation_strategy.hpp"

namespace lattice_boltzmann_method 
{
    /*
        @brief creates a StepSimulationStrategyParser class based on what is written in a file or in argv arguments
    */
    template <int dim>
    class StepSimulationStrategyParser {
        public:
            StepSimulationStrategyParser()=default;

            virtual std::ostream& 
            PrintTerminalHelp(std::ostream &output_stream);

            virtual std::ostream&
            PrintFileHelp(std::ostream &output_stream);

            virtual std::shared_ptr<StepSimulationStrategy<dim>> 
            Parse(int &argc, char *argv[]);

            virtual std::shared_ptr<StepSimulationStrategy<dim>>
            ParseFromFile(const std::string &path);
            
    };

}

#include "step_simulation_strategy_parser.cpp"

#endif // STEP_SIMULATION_STRATEGY_PARSER_HPP
