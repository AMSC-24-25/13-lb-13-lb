#include "openmp_step_simulation_strategy.hpp"

namespace lattice_boltzmann_method {

    template <int dim>
    void OpenMPStepSimulationStrategy<dim>::Initialize(std::shared_ptr<Domain<dim>> domain, 
                            std::vector<std::shared_ptr<NodeCallback<dim>>> node_callbacks,
                            double starting_time,
                            double time_step,
                            unsigned int num_threads) {
        this->Initialize_(domain, node_callbacks, starting_time, time_step); 
        this->SetNumThreads(num_threads);
    }

    template <int dim>
    void OpenMPStepSimulationStrategy<dim>::Setup() {
        // partitioning the domain. One subdomain for each thread
        this->domain_->Partition(this->num_threads_);

        // saving the subdomain pointers
        for ( int i=0; i < this->num_threads_; i++ ) {
            subdomains_.push_back(this->domain_->GetSubDomainPtr(i));
        }
    }

    template <int dim>
    void OpenMPStepSimulationStrategy<dim>::SimulateNextStep() {
        #pragma omp parallel
        {
            int thread_num = omp_get_thread_num();
            std::shared_ptr<Subdomain<dim>> subdomain = subdomains_[thread_num];

            for ( std::shared_ptr<Node<dim>>& nodePtr : *subdomain ) {
                nodePtr->Collide();
                nodePtr->Propagate();
                this->RunConstCallbacks(*nodePtr);
            }
        }
        this->current_time_ += this->time_step_;
    }

}