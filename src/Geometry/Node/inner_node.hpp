#ifndef INNER_NODE_HPP
#define INNER_NODE_HPP

#include "../Point/point.hpp"
#include "node.hpp"

namespace lattice_boltzmann_method {

    template <int dim>
    class InnerNode : public Node<dim> {
    public:
        explicit InnerNode(const Point<double, dim>& position, unsigned int num_directions, Point<double, dim> initial_velocity, double rho)
            : Node<dim>(position, num_directions, initial_velocity, rho) {}

        void Collide() override;
        void Propagate() override;

        void UpdateDensity() override;
        void UpdateVelocity() override;
        void UpdatePressure() override;

        double GetPressure() const override { return _pressure; }

        void SetDistribution(int index, double value) override {
            if (index >= 0 && index < this->_f.size()) {
                this->_f[index] = value;
            }
        }

        double GetDistribution(int index) const override {
            if (index >= 0 && index < this->_f.size()) {
                return this->_f[index];
            }
            return 0.0;
        }

    private:          
        double _pressure;          
    };

}

#include "inner_node.cpp"

#endif // INNER_NODE_HPP
