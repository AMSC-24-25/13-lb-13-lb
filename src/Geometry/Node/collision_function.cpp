#include "collision_function.hpp"

namespace lattice_boltzmann_method {

    template<int dim>
    void CollisionFunction<dim>::ApplyCollision(InnerNode<dim>& node) {
        ComputeEquilibrium(node);
        ComputeFNext(node);
    }

    template<int dim>
    void CollisionFunction<dim>::ComputeEquilibrium(InnerNode<dim>& node) {
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

            node.SetEquilibriumDistribution(
                i,
                weights_[i] * node.GetDensity() * (1.0 + (3.0 * ci_u) + (4.5 * ci_u_squared) - (1.5 * u_squared))
            );
        }
    }

    template<int dim>
    void CollisionFunction<dim>::ComputeFNext(InnerNode<dim>& node) {
        for (size_t i = 0; i < num_distributions_; ++i) {
            double f = node.GetF(i);
            double f_eq = node.GetEquilibriumDistribution(i);

            node.SetF(i, (1 - 1 / tau_) * f + (1 / tau_) * f_eq);
        }
    }
}
