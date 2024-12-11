#include "openmp_step_simulation_strategy.hpp"

namespace lattice_boltzmann_method {
    template <int dim>
    void OpenMPStepSimulationStrategy<dim>::Setup() {
        // partitioning the domain. One subdomain for each thread
        this->domain_.Partition(this->num_threads_);

        // saving the subdomain pointers
        for ( int i=0; i < this->num_threads_; i++ ) {
            subdomains_.push_back(this->domain_.GetSubdomainPtr(i));
        }
    }

    template <int dim>
    void OpenMPStepSimulationStrategy<dim>::SimulateNextStep() {
        #pragma omp parallel
        {
            int thread_num = omp_get_thread_num();
            std::shared_ptr<Subdomain<dim>> subdomain = subdomains_[i];

            for ( std::shared_ptr<Node<dim>>& node : subdomain ) {
                node->Collide();
                node->Propagate();
                this->RunConstCallbacks(node.get());
            }
        }
        current_time_ += time_step_;
    }

}