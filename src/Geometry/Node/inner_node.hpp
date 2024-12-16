#ifndef INNER_NODE_HPP
#define INNER_NODE_HPP

#include "../Geometry/Node/node.hpp"

namespace lattice_boltzmann_method {

    template <int dim>
    class InnerNode : public Node<dim> {
    public:
        explicit InnerNode(const Point<double, dim>& position, int num_distributions)
            : Node<dim>(position), _f(num_distributions, 0.0), _f_eq(num_distributions, 0.0) {}

        void Collide() override;
        void Propagate() override;

        double GetDensity() const;  
        const std::vector<double>& GetVelocity() const;

        void SetF(int index, double f_next) {  
            if (index >= 0 && index < _f.size()) {
                _f[index] = f_next;
            }
        }

        double GetF(int index) const {  
            if (index >= 0 && index < _f.size()) {
                return _f[index];
            }
            return 0.0;
        }

        const std::vector<double>& GetF() const { return _f; }
        const std::vector<double>& GetFEquilibrium() const { return _f_eq; }

        void SetEquilibriumDistribution(int index, double value) { _f_eq[index] = value; }
        double GetEquilibriumDistribution(int index) const { return _f_eq[index]; }

        void UpdateDensity();
        void UpdateVelocity();
        void UpdatePressure();

    private:
        std::vector<double> _f;    // Vettore delle distribuzioni attuali
        std::vector<double> _f_eq; // Vettore delle distribuzioni di equilibrio
    };

}

#endif