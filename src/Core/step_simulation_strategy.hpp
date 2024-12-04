#ifndef STEP_SIMULATION_STRATEGY_HPP
#define STEP_SIMULATION_STRATEGY_HPP

#include "node_callback.hpp"
#include <memory>
#include <vector>

namespace lattice_boltzmann_method 
{
    /*
        Abstract class that represents a strategy for simulating/calculating the values at the next time step with the Lattice Boltzmann Method (LBM). 

        This class is very general (indeed it is abstract), making it possible to implement many version of the LBM. 
        At its's core, it uses a lattice_boltzmann_method::Domain object to access the nodes that compose the physical domain of the problem and 
        it interacts with each node. 

        Also, some lattice_boltzmann_method::NodeCallback objects might be provided if some action needs to be performed on the node after this class
        interacted with it. 
        The user might expect the class to do so:
            for { auto node : collection_of_nodes } {
                node.DoSomething()
                for { auto node_callback : collection_of_callbacks } {
                    node_callback.HandleNode(node)
                }
            }

        A concrete implementation of this class might be parallel.
    */
    class StepSimulationStrategy {
        public:
            StepSimulationStrategy(/*Domain &domain, */std::unique_ptr<NodeCallback> node_callback=nullptr) {
                node_callbacks_.push_back(std::move(node_callback));
            }
            StepSimulationStrategy(std::vector<std::unique_ptr<NodeCallback>> node_callbacks) {
                node_callbacks_.reserve(node_callbacks.size());
                for ( int i=0; i<node_callbacks.size(); i++ ) {
                    if ( node_callbacks[i]) {
                        node_callbacks_.push_back(std::move(node_callbacks[i]));
                    }
                }
            }

            void AddNodeCallback(std::unique_ptr<NodeCallback> node_callback)  { 
                if ( node_callback ) {
                    node_callbacks_.push_back(std::move(node_callback));
                }
            }
            //Domain domain_;

            /*
                @brief calculates the next step of the simulation, which means it advances by a certain deltaT in the simulation
                It is not constant since it changes the nodes
            */
            virtual void SimulateNextStep()=0;

            /*
                @brief calculates the steps of the simulation until `time` is reached, stepping by a certain deltaT at each iteration
                It is not constant since it changes the nodes
            */
            virtual void SimulateUntil(double time)=0;
        protected:
            std::vector<std::unique_ptr<NodeCallback>> node_callbacks_;
        private:
    };

    class SerialStepSimulationStrategy : public StepSimulationStrategy {
        public:
            SerialStepSimulationStrategy(std::unique_ptr<NodeCallback> node_callback) : StepSimulationStrategy{std::move(node_callback)} {}
            virtual void SimulateNextStep() override;
            virtual void SimulateUntil(double time) override;
        private:
    };
}

#endif