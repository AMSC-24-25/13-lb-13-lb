#ifndef SIMULATION_OBSERVER_HPP
#define SIMULATION_OBSERVER_HPP

#include <memory>

#include "../History/step.hpp"

namespace lattice_boltzmann_method {
    /*
        This class implements an observer-observable pattern with SimulationObservable. In particular, it is an observable.

        A class that wants to be notified when a new simulation step is performed, must inherit from this class and then subscribe (or be subscribed) to an
        object that inherits from SimulationObservable (tipically, a StepSimulationStrategy).

    */
    class SimulationObserver {
        public:
            virtual void AddStep(Step &step) = 0;
            virtual void AddStep(const Step &step) = 0;
    };

    /*
        This class implements an observer-observable pattern with SimulationObserver. In particular, it is an observable.

        A class that generates Step(s) and wants to notify some other classes, might want to inherit from this class.
    */
    class SimulationObservable {
        public:

            /* 
                Registers an observer to the list of observers
            */
            virtual void RegisterObserver(std::shared_ptr<SimulationObserver> observer) {
                observers_.push_back(observer);
            }

            /*
                Notifies all the observers by giving them a non-const reference to the Step object
            */
            virtual void NotifyAll(Step& step) const {
                for ( std::shared_ptr<SimulationObserver> observer : observers_ ) {
                    observer->AddStep(step);
                }
            }

            /*
                Notifies all the observers by giving them a const reference to the Step object
            */
            virtual void NotifyAllConst(const Step& step) const {
                for ( std::shared_ptr<SimulationObserver> observer : observers_ ) {
                    observer->AddStep(step);
                }
            }
        protected:
            std::vector<std::shared_ptr<SimulationObserver>> observers_;
    };
}

#endif // SIMULATION_OBSERVER_HPP
