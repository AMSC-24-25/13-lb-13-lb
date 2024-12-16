#include "inner_node.hpp"

namespace lattice_boltzmann_method {

    template <int dim>
    void InnerNode<dim>::Collide() {
        // Implementazione della collisione
    }

    template <int dim>
    void InnerNode<dim>::Propagate() {
        // Implementazione della propagazione
    }

    template <int dim>
    double InnerNode<dim>::GetDensity() const {
        double rho = 0.0;
        for (const auto& f_val : _f) {
            rho += f_val;
        }
        return rho;
    }

    template <int dim>
    const std::vector<double>& InnerNode<dim>::GetVelocity() const {
        static std::vector<double> velocity(dim, 0.0);
        double rho = GetDensity();

        if (rho > 0) {
            for (int d = 0; d < dim; ++d) {
                velocity[d] = 0.0;
                for (size_t i = 0; i < _f.size(); ++i) {
                    velocity[d] += _f[i] * GetDirection(i)[d];
                }
                velocity[d] /= rho;
            }
        }
        return velocity;
    }

    template <int dim>
    void InnerNode<dim>::UpdateVelocity() {
        const auto& velocity = GetVelocity();
        for (int d = 0; d < dim; ++d) {
            this->_velocity[d] = velocity[d];
        }
    }

    template <int dim>
    void InnerNode<dim>::UpdateDensity() {
        double rho = GetDensity();
        this->_density = rho;
    }

    template <int dim>
    void InnerNode<dim>::UpdatePressure() {
        this->_pressure = GetDensity() * GetVelocity().size();
    }
}
