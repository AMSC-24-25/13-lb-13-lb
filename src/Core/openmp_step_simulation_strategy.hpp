#ifndef OPENMP_STEP_SIMULATION_STRATEGY_HPP
#define OPENMP_STEP_SIMULATION_STRATEGY_HPP

#include "step_simulation_strategy.hpp"
#include <omp.h>
#include <cmath>

namespace lattice_boltzmann_method {
    template <int dim>
    class OpenMPStepSimulationStrategy : public StepSimulationStrategy<dim> {
        public:
            OpenMPStepSimulationStrategy(Domain<dim> &domain, 
                                         std::unique_ptr<NodeCallback<dim>> node_callback,
                                         double       starting_time = 0.0,
                                         double       time_step     = 0.1,
                                         unsigned int num_threads   = 8) 
                : StepSimulationStrategy<dim>{domain, std::move(node_callback), starting_time, time_step},
                  num_threads_{num_threads} {
                    omp_set_max_active_levels(256);
                }
            virtual void SetNumThreads(unsigned int num_threads) {
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

#endif // OPENMP_STEP_SIMULATION_STRATEGY_HPP