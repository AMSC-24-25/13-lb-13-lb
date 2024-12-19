#ifndef COLLISION_FUNCTION_CPP
#define COLLISION_FUNCTION_CPP

#include "collision_function.hpp"

namespace lattice_boltzmann_method {

    template<int dim>
    void CollisionFunction<dim>::ApplyCollision(InnerNode<dim>& node) const {
        node.UpdateDensity();
        node.UpdateVelocity();
        node.UpdatePressure();

        std::vector<double> f = node.GetDistributions();
        std::vector<double> f_eq = node.GetEquilibriumDistributions();

        for (size_t i = 0; i < num_distributions_; ++i) {
            double ci_u = 0.0;
            for (int d = 0; d < dim; ++d) {
                ci_u += directions_[i][d] * node.GetVelocity()[d];
            }

            double ci_u_squared = ci_u * ci_u;
            double u_squared = 0.0;
            for (int d = 0; d < dim; ++d) {
                u_squared += node.GetVelocity()[d] * node.GetVelocity()[d];
            }

            f_eq[i] = weights_[i] * node.GetDensity() * (1.0 + (3.0 * ci_u) + (4.5 * ci_u_squared) - (1.5 * u_squared));
            f[i] = (1 - 1 / tau_) * f[i] + (1 / tau_) * f_eq[i];
        }
    }
}

#endif