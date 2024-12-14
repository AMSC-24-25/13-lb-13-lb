#ifndef OPENMP_STEP_SIMULATION_STRATEGY_HPP
#define OPENMP_STEP_SIMULATION_STRATEGY_HPP

#include "step_simulation_strategy.hpp"
#include <omp.h>
#include <cmath>

namespace lattice_boltzmann_method {
    template <int dim>
    class OpenMPStepSimulationStrategy : public StepSimulationStrategy<dim> {
        public:
            OpenMPStepSimulationStrategy() = default;

            OpenMPStepSimulationStrategy(std::shared_ptr<Domain<dim>> domain, 
                                         std::shared_ptr<NodeCallback<dim>> node_callback,
                                         double       starting_time = 0.0,
                                         double       time_step     = 0.1,
                                         unsigned int num_threads   = 8) 
                : StepSimulationStrategy<dim>{domain, node_callback, starting_time, time_step},
                  num_threads_{num_threads} {
                    omp_set_max_active_levels(256);
                    //if ( num_threads == 0 ) throw new Exception()
                }
            
            void Initialize(std::shared_ptr<Domain<dim>> domain, 
                            std::vector<std::shared_ptr<NodeCallback<dim>>> node_callbacks,
                            double starting_time = 0.0,
                            double time_step = 0.1,
                            unsigned int num_threads = 8);

            virtual void SetNumThreads(unsigned int num_threads) {
                if ( num_threads == 0 ) return;

                num_threads_ = num_threads;
                omp_set_num_threads(num_threads);
            };
            virtual void Setup() override;
            virtual void SimulateNextStep() override;
        private:
            unsigned int num_threads_;
            std::vector<std::shared_ptr<Subdomain<dim>>> subdomains_;

    };
}

#include "openmp_step_simulation_strategy.cpp"

#endif // OPENMP_STEP_SIMULATION_STRATEGY_HPP
