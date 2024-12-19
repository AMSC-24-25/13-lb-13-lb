#ifndef COLLISION_FUNCTION_HPP
#define COLLISION_FUNCTION_HPP

#include "node.hpp"
#include "inner_node.hpp"

namespace lattice_boltzmann_method {

    template<int dim>
    class CollisionFunction {
    public:
        
        static CollisionFunction<dim>& CreateInstance(const std::vector<std::vector<double>>& directions,
                                                 const std::vector<double>& weights,
                                                 double reynolds_number,
                                                 double characteristic_velocity,
                                                 double characteristic_length) {
            if ( !instance_created_ ) {
                instance_(directions, weights, reynolds_number, characteristic_velocity, characteristic_length);
                instance_created_ = true;
            }
            return instance_;
        }
        static CollisionFunction<dim>& GetInstance() {
            return instance_;
        }

        void ApplyCollision(InnerNode<dim>& node) const;

    private:
        static inline bool instance_created_ = false;
        static inline CollisionFunction<dim> instance_;

        CollisionFunction() {};
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

        CollisionFunction(const CollisionFunction&) = delete;
        CollisionFunction& operator=(const CollisionFunction&) = delete;

        std::vector<std::vector<double>> directions_;  
        std::vector<double> weights_;                 
        size_t num_distributions_;
        double tau_;
    };
}

#include "collision_function.cpp"

#endif