#ifndef SIMULATION_MANAGER_HPP
#define SIMULATION_MANAGER_HPP

#include <memory>

#include "step_simulation_strategy.hpp"

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
            3. by passing through command line a path to a .json file through the option `-parameters`
    */
    template<int dim>
    class SimulationManager 
    {
        public:
            SimulationManager(int argc, char *argv[], std::unique_ptr<StepSimulationStrategy<dim>> step_strategy=nullptr) : step_strategy_{std::move(step_strategy)} {
                /* Parsing arguments from cli*/
                // ...
            }

            void Start();

        protected:
            std::unique_ptr<StepSimulationStrategy<dim>> step_strategy_;

            virtual void LoadDomain();
            virtual void SetupDomain();
    };

}

#include "simulation_manager.cpp"

#endif