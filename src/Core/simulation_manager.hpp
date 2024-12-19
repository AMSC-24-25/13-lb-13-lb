#ifndef SIMULATION_MANAGER_HPP
#define SIMULATION_MANAGER_HPP

#include <memory>
#include <string>

#include "StepSimulationStrategy/step_simulation_strategy.hpp"
#include "StepSimulationStrategy/Parser/step_simulation_strategy_parser.hpp"
#include "../History/history.hpp"
#include "../History/Parser/history_parser.hpp"

#include "../Geometry/Node/node.hpp"
#include "../Geometry/Node/inner_node.hpp"
#include "../Geometry/Node/bounce_back_node.hpp"

namespace lattice_boltzmann_method
{

    /*
        Class that manages the whole iteration. Parameters of the problem (domain/mesh, fluid parameters, ...) can be passed in many ways as explained later.
        Briefly, this class set ups the domain and the parameters, then executes iteratively the a certain lattice_boltzmann_method::StepSimulationStrategy.
        It handles also the simulation output.

        Passing parameter to SimulationManager
        Parameters can be passed in 3 ways:
            1. from the command line through the command line parameters (eg. -Re sets the reynold number of the fluid). See later for further details
                - Obviously, the mesh cannot be passed through the command line; pass instead the path
            2. by passing a LatticeBoltzmannParameter object when constructing the object
            3. by passing a path to a file in which everything is contained
    */
    template<int dim>
    class SimulationManager 
    {
        public:
            /*
                @brief Initializes the SimulationManager from the command line
            */
            SimulationManager(int &argc, char *argv[],
                        std::shared_ptr<StepSimulationStrategyParser<dim>> simulation_strategy_parser,
                        std::shared_ptr<HistoryParser> history_parser) {
                this->Parse_(simulation_strategy_parser, history_parser, argc, argv);
            }

            /*
                @brief Initializes the SimulationManager from the command line but with 
                       step_strategy and history given by the caller
            */
            SimulationManager(int argc, char *argv[],
                              std::shared_ptr<StepSimulationStrategy<dim>> step_strategy,
                              std::shared_ptr<History> history)
                : step_strategy_{step_strategy}, history_{history} {}

            /*
                @brief Initializes the SimulationManager from a file
            */
            SimulationManager(const std::string &path,
                        std::shared_ptr<StepSimulationStrategyParser<dim>> simulation_strategy_parser,
                        std::shared_ptr<HistoryParser> history_parser) {
                this->ParseFromFile_(simulation_strategy_parser, history_parser, path);
            }

            /*
                @brief Starts the simulation
            */
            void Start();

        protected:
            std::shared_ptr<StepSimulationStrategy<dim>> step_strategy_;
            std::shared_ptr<History> history_;

            static constexpr int _k_domain_length = 1000;  // to be read from file
            std::shared_ptr<Domain<2>> _domain;    // don't know if this has to be here, just putting for later

            virtual void Parse_(std::shared_ptr<StepSimulationStrategyParser<dim>> simulation_strategy_parser,
                              std::shared_ptr<HistoryParser> history_parser,
                               int &argc, char *argv[]);
                        
            virtual void ParseFromFile_(std::shared_ptr<StepSimulationStrategyParser<dim>> simulation_strategy_parser,
                              std::shared_ptr<HistoryParser> history_parser,
                              const std::string &path);

            virtual void LoadDomain();
            virtual void SetupDomain();
    };

}

#include "simulation_manager.cpp"

#endif // SIMULATION_MANAGER_HPP
