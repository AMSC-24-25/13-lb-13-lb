#include "inner_node.hpp"
#include <cmath>

#include "inner_node.hpp"
#include "collision_function.hpp"

namespace lattice_boltzmann_method {

    template <int dim>
    void InnerNode<dim>::Collide() {
        auto& collision_function = CollisionFunction<dim>::Instance(
            Node<dim>::directions,
            Node<dim>::weights,
            Node<dim>::ReynoldsNumber,
            Node<dim>::CharacteristicVelocity,
            Node<dim>::CharacteristicLength
        );
        collision_function.ApplyCollision(*this);
    }

    template <int dim>
    void InnerNode<dim>::Propagate() {
        for (size_t i = 0; i < Node<dim>::directions.size(); ++i) {
            auto destination_position = this->GetPosition();
            for (int d = 0; d < dim; ++d) {
                // TODO non usare ::directions ma GetDirections
                destination_position[d] += Node<dim>::directions[i][d];
            }

            // TODO: usare i vicini e non GetNeighbourNode
            InnerNode<dim>* neighbor = GetNeighborNode(destination_position);
            if (neighbor) {
                neighbor->SetDistribution(i, this->GetDistribution(i));
            }
        }
    }

    template <int dim>
    void InnerNode<dim>::UpdateDensity() {
        _density = 0.0;
        for (const auto& f_val : _f) {
            _density += f_val;
        }
    }

    template <int dim>
    void InnerNode<dim>::UpdateVelocity() {
        _velocity = Point<double, dim>{};
        for (size_t i = 0; i < _f.size(); ++i) {
            for (int d = 0; d < dim; ++d) {
                // TODO non usare ::directions ma GetDirections
                _velocity[d] += _f[i] * Node<dim>::directions[i][d];
            }
        }
        for (int d = 0; d < dim; ++d) {
            _velocity[d] /= _density;
        }
    }

    template <int dim>
    void InnerNode<dim>::UpdatePressure() {
        constexpr double sound_speed = 1.0 / std::sqrt(3.0) * Node<dim>::DeltaX / Node<dim>::DeltaT;
        _pressure = _density * sound_speed * sound_speed;
    }

}