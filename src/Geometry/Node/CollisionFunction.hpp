#ifndef COLLISION_FUNCTION_HPP
#define COLLISION_FUNCTION_HPP

#include "../Geometry/Node/node.hpp"

namespace lattice_boltzmann_method {

    template<int dim>
    class CollisionFunction {
    public:
        CollisionFunction(const std::vector<std::vector<double>>& directions,
                          const std::vector<double>& weights,
                          double reynolds_number,
                          double characteristic_velocity,
                          double characteristic_length)
            : directions_(directions),
              weights_(weights),
              num_distributions_(weights.size()) {

            tau_ = 0.5 + (3.0 * characteristic_velocity * characteristic_length) / reynolds_number;
        }

        void ApplyCollision(Node<dim>& node);

    private:
        std::vector<std::vector<double>> directions_;  // Vettori delle direzioni c_i
        std::vector<double> weights_;                 // Pesi w_i
        size_t num_distributions_;
        double tau_;
    };

}

#endif
