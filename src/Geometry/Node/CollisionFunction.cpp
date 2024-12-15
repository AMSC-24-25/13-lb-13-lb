#include "collision_function.hpp"

namespace lattice_boltzmann_method {

    template<int dim>
    void CollisionFunction<dim>::ApplyCollision(Node<dim>& node) {
      //  auto innerNode = dynamic_cast<InnerNode<dim>*>(&node);
        if (innerNode) {
            double rho = innerNode->GetDensity();
          //  auto& f = innerNode->_f;
           // auto& f_eq = innerNode->_f_eq;

            for (size_t i = 0; i < num_distributions_; ++i) {
                double ci_u = innerNode->GetVelocity() * innerNode->GetDirection(i);

                double equilibrium = weights_[i] * rho * (1.0 + (ci_u / c_s2) + (ci_u * ci_u) / (2 * c_s4) -
                                                         (innerNode->GetVelocity().norm() * innerNode->GetVelocity().norm()) / (2 * c_s2));

                f_eq[i] = equilibrium;
                f[i] = (1 - 1 / tau_) * f[i] + 1 / tau_ * f_eq[i];
            }
        }
    }
}
